/*
 * C Program to Perform Binary Search using Recursion
 */
 
#include <stdio.h>
#include <stdlib.h>
//Import the OpenMP Library
#include <omp.h>
 
void binary_search(int [], int, int, int);
void bubble_sort(int [], int);
int randNumber(int, int);
 
int main()
{
    int key, size, i;
    int list[25];
 
    printf("Enter size of a list: ");
    //change manual input to static input
    size = 50;
    printf("%d", size);
    // Add the parallel sentence
    #pragma omp parallel shared (list, size) private(i)
    {
        /*
        parallel the input for, doing this the system
        hasn't had to wait the user to type all inputs 
        of the list
        */ 
        #pragma omp parallel for
        for(i=0; i < size; i++){
            list[i] = randNumber(0,1000);
        }
    }
    bubble_sort(list, size);
    printf("\n");
    printf("key to search: 300\n"); //change dinamic input to static
    key = 300;
    binary_search(list, 0, size, key); 
}
 
void bubble_sort(int list[], int size)
{
    int temp, i, j;
    #pragma omp parallel shared (list, size, temp) private(i, j)
    {
        // parallel the sort Funtion
        #pragma omp parallel for
        for(i = 0; i < size; i++){
            for(j = i; j < size; j++){
                if (list[i] > list[j]){
                    temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
            }
        }
    }
}
 
void binary_search(int list[], int lo, int hi, int key)
{
    int mid;
 
    if (lo > hi)
    {
        printf("Key not found\n");
        return;
    }
    mid = (lo + hi) / 2;
    if (list[mid] == key)
    {
        printf("Key found\n");
    }
    else if (list[mid] > key)
    {
        binary_search(list, lo, mid - 1, key);
    }
    else if (list[mid] < key)
    {
        binary_search(list, mid + 1, hi, key);
    }
}
//Function to create a random number to fill the array
int randNumber (int min, int max){
    return (int)(((double)rand()/RAND_MAX)*(max-min)+min);
}