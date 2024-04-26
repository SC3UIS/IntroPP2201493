#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main(int argc, char *argv[]){
    setenv("OMPI_MCA_btl", "^openib", 1);
    setenv("OMPI_MCA_orte_base_help_aggregate", "0", 1);
    // MPI Start
    MPI_Init(&argc, &argv);
    int rank, size, key, i;
    const int n = 100000;
    int list[n];

    // Get the process range and the communicator size.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(0) + rank);

    // Split the list between the MPI process.
    int sublist_size = n / size;
    int sublist[sublist_size];

    // Distribute the list between the MPI process.
    MPI_Scatter(list, sublist_size, MPI_INT, sublist, sublist_size, MPI_INT, 0, MPI_COMM_WORLD);

	clock_t start, end;
    double cpu_time_used;
    start = clock();
    bubble_sort(sublist, sublist_size);

    int *merged_list = NULL;
    if (rank == 0){
        merged_list = (int *)malloc(n * sizeof(int));
    }
    MPI_Gather(sublist, sublist_size, MPI_INT, merged_list, sublist_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Sync all process before to calculate the whole time.
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0){
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tiempo tomado para ordenar la lista: %lf seconds\n", cpu_time_used);
    }
    printf("Enter key to search: ");
    scanf("%d", &key);

    // Transmit the search key to all process.
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each MPI process do the binary search.
    start = clock(); // Start temp.
    binary_search(sublist, 0, sublist_size - 1, key);
    end = clock(); // Stop temp.

    // Sync all process before calculate the total time.
    MPI_Barrier(MPI_COMM_WORLD);

    // Only the root process print the search time.
    if (rank == 0){
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time to find the key: %lf seconds\n", cpu_time_used);
    }
    // MPI END.
    MPI_Finalize();
    return 0;
}

// Function to sort the list using bubble sort.
void bubble_sort(int list[], int size){
    int temp, i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size - 1 - i; j++){
            if (list[j] > list[j + 1]){
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

// Function to do the Binary Search
void binary_search(int list[], int lo, int hi, int key){
    int mid;

    // If 'hi' is bigger, the key doesn't be in the list.
    if (lo > hi){
        printf("Key not found\n");
        return;
    }
    // Calculate the middle point
    mid = (lo + hi) / 2;
    // If the key be in the middle point.
    if (list[mid] == key){
        printf("Key found\n");
    }
    // If the key are in the left half.
    else if (list[mid] > key){
        binary_search(list, lo, mid - 1, key);
    }
    // If the key are in the right half.
    else if (list[mid] < key){
        binary_search(list, mid + 1, hi, key);
    }
}