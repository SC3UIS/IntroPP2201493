#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void arrange(int, int);
int generateRandom();

// Variables globales
int array[100000], array1[100000]; // Arreglos para almacenar los números y su copia
int i, j, temp, max, count = 100000, maxdigits = 0, c = 0; // Variables de control y temporales
double start, end; // Variables para medir el tiempo de ejecución

int main(int argc, char** argv) {
    // Inicializa MPI
    MPI_Init(NULL, NULL);

    // Obtiene el número total de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtiene el rango del proceso actual
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int t1, t2, k, t, n = 1;

    // El proceso 0 recibe los datos del usuario
    if (world_rank == 0) {
        start = MPI_Wtime(); // Iniciar el cronómetro

        // Generar números aleatorios y almacenarlos en array1 y array
        srand(time(NULL)); // Inicializar la semilla del generador de números aleatorios
        for (i = 0; i < 100000; i++) {
            array1[i] = generateRandom(); // Generar un número aleatorio
            array[i] = array1[i]; // Almacenar el mismo número en array
        }
    }

    // Se envían los datos a todos los procesos
    MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array, count, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array1, count, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular el número máximo de dígitos en los números del arreglo
    for (i = 0; i < count; i++)
    {
        t = array[i]; // Primer elemento en t
        while(t > 0)
        {
            c++;
            t = t / 10; // Encontrar el dígito más significativo (MSB)
        }
        if (maxdigits < c)
            maxdigits = c; // Número de dígitos de cada número
        c = 0;
    }
    while (--maxdigits)
        n = n * 10;

    // Cada proceso ordena su parte del arreglo
    int chunk_size = count / world_size;
    int start_index = world_rank * chunk_size;
    int end_index = (world_rank == world_size - 1) ? count : (world_rank + 1) * chunk_size;

    // Ordenar los números utilizando el algoritmo de "Postman sort"
    for (i = start_index; i < end_index; i++)
    {
        max = array[i] / n; // MSB - Dividir por la base particular
        t = i;
        for (j = i + 1; j < count; j++)
        {
            if (max > (array[j] / n))
            {
                max = array[j] / n; // Mayor MSB
                t = j;
            }
        }
        // Intercambiar elementos en array1
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        // Intercambiar elementos en array
        temp = array[t];
        array[t] = array[i];
        array[i] = temp;
    }

    // Sincronizar para asegurar que todos los procesos han completado la fase de ordenación
    MPI_Barrier(MPI_COMM_WORLD);

    // Cada proceso ordena su parte del arreglo con la misma base
    while (n >= 1)
    {
        for (i = start_index; i < end_index;)
        {
            t1 = array[i] / n;
            for (j = i + 1; t1 == (array[j] / n); j++);
            arrange(i, j); // Llamar a la función arrange para ordenar
            i = j;
        }
        n = n / 10;

        // Sincronizar para asegurar que todos los procesos han completado esta fase de ordenación
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Fusionar los resultados de todos los procesos
    MPI_Gather(array1 + start_index, chunk_size, MPI_INT, array1, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        // Ordenar los números fusionados
        arrange(0, count);

        end = MPI_Wtime(); // Detener el cronómetro
        printf("Work took %f seconds\n", end - start); // Imprimir el tiempo de ejecución
    }

    // Finaliza MPI
    MPI_Finalize();

    return 0;
}

/* Function to arrange the of sequence having same base */
void arrange(int k,int n)
{
    for (i = k; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (array1[i] > array1[j])
            {
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

// Generar un número aleatorio entre 1 y 100000
int generateRandom() {
    return rand() % 100000 + 1;
}