/* 
 * C Program to Implement Postman Sort Algorithm
 */
#include <stdio.h>
// Import OpenMP Library and stdLib for random numbers
#include <omp.h>
#include <stdlib.h>
 
void arrange(int,int);
int randNumber(int, int);  //add declaration function
int array[100], array1[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;
 
void main()
{
    int t1, t2, k, t, n = 1;
 
    printf("Enter size of array: 50"); //change dinamic input to a static input
    count = 50;
    #pragma omp parallel shared (count, array, array1, t, maxdigits, c) private(i)
    {
        //set in all input data in random way
        #pragma omp parallel for
        for (i = 0; i < count; i++){
            array[i] = randNumber(0, 10000);
            array1[i] = array[i];            
        }
        // Finding Max length of the biggest number
        #pragma omp parallel for
        for (i = 0; i < count; i++){
            t = array[i];        /*first element in t */
            while(t > 0){
                c++;
                t = t / 10;        /* Find MSB */
            }
        if (maxdigits < c) 
            maxdigits = c;   /* number of digits of a each number */
            c = 0;
        }
    }
    while(--maxdigits) 
        n = n * 10;      
    #pragma omp parallel shared (count, array, array1, t, max, n) private(i, j)
    {
    for (i = 0; i < count; i++){
        max = array[i] / n;        /* MSB - Dividnng by perticular base */
        t = i;
        for (j = i + 1; j < count;j++){
            if (max > (array[j] / n)){
                max = array[j] / n;   /* greatest MSB */
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
    }
    while (n >= 1){
        #pragma omp parallel shared (count, t1, array, n) private(i, j)
        {
            #pragma omp parallel for //parallel the sorting function
            for (i = 0; i < count;){
                t1 = array[i] / n;
                for (j = i + 1; t1 == (array[j] / n); j++);
                    arrange(i, j);
                i = j;
            }
        }
        n = n / 10;
    }
    printf("\nSorted Array (Postman sort) :");    
    for (i = 0; i < count; i++)
        printf("%d ", array1[i]);
    printf("\n");
}
 
/* Function to arrange the of sequence having same base */
void arrange(int k,int n){
    #pragma omp parallel shared (k, n, array, array1, n, temp) private(i, j)
    {
        #pragma omp parallel for 
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
}
//Function to create a random number to fill the array
int randNumber (int min, int max){
    return (int)(((double)rand()/RAND_MAX)*(max-min)+min);
}