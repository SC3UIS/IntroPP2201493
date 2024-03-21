## OpenMP

Aquí se encuentra el desarrollo de la primera evaluación de Introducción a la Computación Paralela.

#### Contenido

Aqui estan los archivos de:

- `BinarySearch.c` y `PostmanSort.c`: Archivo suministrado por el docente. Consiste en dos metodos de ordenamiendo de listas.
- `OMP_BinarySearch.c` y `OMP_PostmanSort.c`: Archivo donde se encuentra las modificaciones pertinentes para la ejecucion en paralelo de las instrucciones de ordenamiento.
- `Binary.sbatch` y `PostmanSort.c`: Archivo para correr automaticamente el código paralelizado en la supercomputadora de Guane. En este mismo documento, más abajo se explica cómo realizarlo.

#### Implementación en *GUANE*

Una idea adicional a la paralelización es poderla implementar en la supercomputadora *GUANE*. Para esto es necesario subir dos archivos *(`OMP_BinarySearch.c`, `Binary.sbatch`)* en nuestra sesión de usuarios, ya sea utilizando SSH.

Nos ubicamos en la carpeta donde se encuentran estos archivos, para posteriormente ejecutar la instrucción 'sbatch omp_addition-and-subtraction-of-matrices.sbach' y esperamos a que haya los recursos disponibles, se desarrolla las instrucciones respectivas y se generan los archivos de salida.

Dentro del archivo '.sbatch' lo que se realiza es solicitar los recursos de la supercomputadora: partición, nombre del trabajo, número de nodos, archivos de salida, entre otros. Aquí se genera el archivo de salida/ejecución del código realizado '.c', que será el que la máquina correrá y dará los resultados en 'output_addition-and-subtraction-of-matrices.txt'