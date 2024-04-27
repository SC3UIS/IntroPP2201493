#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function declaration
void arrange(int, int);
int generateRandom();

// Global variables
int array[100000], array1[100000];
int i, j, temp, max, count = 100000, maxdigits = 0, c = 0;
double start, end;

int main(int argc, char** argv) {
    // MPI Starts
    MPI_Init(NULL, NULL);

    // Get the total number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the range of the current process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int t1, t2, k, t, n = 1;

    // Process 0 receives user input.
    if (world_rank == 0) {
        start = MPI_Wtime(); 

        // Generate random numbers and store them in array1 and array2.
        srand(time(NULL)); // Initialize the seed of the random number generator.
        for (i = 0; i < 100000; i++) {
            array1[i] = generateRandom();
            array[i] = array1[i];
        }
    }

    // The data is sent to all processes.
    MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array, count, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array1, count, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the maximum number of digits in the numbers of the array.
    for (i = 0; i < count; i++){
        t = array[i];
        while(t > 0){
            c++;
            t = t / 10;
        }
        if (maxdigits < c)
            maxdigits = c;
        c = 0;
    }
    while (--maxdigits)
        n = n * 10;

    // Each process sorts its portion of the array.
    int chunk_size = count / world_size;
    int start_index = world_rank * chunk_size;
    int end_index = (world_rank == world_size - 1) ? count : (world_rank + 1) * chunk_size;

    // Sort the numbers using the Postman sort algorithm.
    for (i = start_index; i < end_index; i++){
        max = array[i] / n;
        t = i;
        for (j = i + 1; j < count; j++){
            if (max > (array[j] / n)){
                max = array[j] / n;
                t = j;
            }
        }
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        temp = array[t];
        array[t] = array[i];
        array[i] = temp;
    }

    // Synchronize to ensure that all processes have completed the sorting phase.
    MPI_Barrier(MPI_COMM_WORLD);

    // Each process sorts its part of the array using the same base.
    while (n >= 1){
        for (i = start_index; i < end_index;){
            t1 = array[i] / n;
            for (j = i + 1; t1 == (array[j] / n); j++);
            arrange(i, j);
            i = j;
        }
        n = n / 10;

        // Synchronize to ensure that all processes have completed this sorting phase.
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Merge the results from all processes.
    MPI_Gather(array1 + start_index, chunk_size, MPI_INT, array1, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        arrange(0, count);
        end = MPI_Wtime();
        printf("Work took %f seconds\n", end - start);
    }

    // MPI Ends
    MPI_Finalize();

    return 0;
}

/* Function to arrange the of sequence having same base */
void arrange(int k,int n){
    for (i = k; i < n - 1; i++){
        for (j = i + 1; j < n; j++){
            if (array1[i] > array1[j]){
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = (array[i] % 10);
                array[i] = (array[j] % 10);
                array[j] = temp;
            }
        }
    }
}

// Generate a random number between 1 and 100000.
int generateRandom() {
    return rand() % 100000 + 1;
}