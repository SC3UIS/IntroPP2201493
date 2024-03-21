## OpenMP

Aquí se encuentra el desarrollo de la primera evaluación de Introducción a la Computación Paralela. Los dos codigos son metodos de ordenamiendo en que el BinarySort utiliza BubbleSort que consiste en iterar sobre la lista varias veces, comparando elementos adyacentes y realizando intercambios si están en el orden incorrecto. En cada iteración, el elemento más grande (o más pequeño, dependiendo del ordenamiento) "burbujea" hacia su posición final; Y el PostmanSort utiliza un metodo de ordenamiento llamado BucketSort en cual cosiste en seleccionar un número de "cubetas" (o "buckets") y distribuye los elementos de la lista en esas cubetas según cierto criterio. Luego, cada cubeta se ordena individualmente, y finalmente, se combinan las cubetas ordenadas para formar la lista ordenada completa.

### Contenido

Aqui estan los archivos de:

- `BinarySearch.c` y `PostmanSort.c`: Archivo suministrado por el docente. Consiste en dos metodos de ordenamiendo de listas.
- `OMP_BinarySearch.c` y `OMP_PostmanSort.c`: Archivo donde se encuentra las modificaciones pertinentes para la ejecucion en paralelo de las instrucciones de ordenamiento.
- `Binary.sbatch` y `PostmanSort.c`: Archivo para correr automaticamente el código paralelizado en la supercomputadora de Guane. En este mismo documento, más abajo se explica cómo realizarlo.
- `output_BinarySearch.txt` y `output_PostmanSort.txt`: Archivo de texto en donde se encuentran las salidas que tiene el código paralelizado. Estas salidas serían las que normalmente se verían en la pantalla o consola al interactuar con el usuario más los adicionales que se coloquen en el archivo '.sbatch'.
- `x_BinarySearch` y `x_PostmanSort`: Archivo binario donde se encuentra compilado el codigo.

## Descripcion

Se parte de una implementación que se ejecuta en un solo hilo, para transformarla en una que se ejecute en paralelo. Se utilizó la librería OpenMP para este propósito, específicamente así:
```c
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
```
Con `#pragma omp parallel` anunciamos que vamos a abrir una región paralela y todo lo que esté dentro de 
las llaves se ejecutará usando todos los hilos, por defecto. Con la directiva `for` que está en el pragma le 
decimos que el ciclo que está abajo divida la ejecución de sus repeticiones en partes iguales para cada hilo. 

## Opciones de compilación
Para compilar se utilizó el compilador *gcc 9.2.0*, de la siguiente manera:
1. `gcc -fopenmp OMP_BinarySearch.c -o x_Binary`: Para compilar el código fuente de nuestra 
solución en paralelo, indicando que utilice *OpenMP*.
2. `./x_Binary`: Para ejecutar el binario que creamos en el primer paso.

### Implementación en *GUANE*

Una idea adicional a la paralelización es poderla implementar en la supercomputadora *GUANE*. Para esto es necesario subir dos archivos *(`OMP_BinarySearch.c`, `Binary.sbatch`)* en nuestra sesión de usuarios, ya sea utilizando SSH.

Nos ubicamos en la carpeta donde se encuentran estos archivos, para posteriormente ejecutar la instrucción 'sbatch omp_addition-and-subtraction-of-matrices.sbach' y esperamos a que haya los recursos disponibles, se desarrolla las instrucciones respectivas y se generan los archivos de salida.

Dentro del archivo '.sbatch' lo que se realiza es solicitar los recursos de la supercomputadora: partición, nombre del trabajo, número de nodos, archivos de salida, entre otros. Aquí se genera el archivo de salida/ejecución del código realizado '.c', que será el que la máquina correrá y dará los resultados en `output_BinarySearch`
