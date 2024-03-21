## OpenMP

Aquí se encuentra el desarrollo de la primera evaluación de Introducción a la Computación Paralela.

#### Contenido

Aqui hay 

#### Implementación en *GUANE*

Una idea adicional a la paralelización es poderla implementar en la supercomputadora *GUANE*. Para esto es necesario subir dos archivos *('omp_addition-and-subtraction-of-matrices.c', 'omp_addition-and-subtraction-of-matrices.sbach')* en nuestra sesión de usuarios, ya sea utilizando JupyterHub o SSH.

Nos ubicamos en la carpeta donde se encuentran estos archivos, para posteriormente ejecutar la instrucción 'sbatch omp_addition-and-subtraction-of-matrices.sbach' y esperamos a que haya los recursos disponibles, se desarrolla las instrucciones respectivas y se generan los archivos de salida.

Dentro del archivo '.sbatch' lo que se realiza es solicitar los recursos de la supercomputadora: partición, nombre del trabajo, número de nodos, archivos de salida, entre otros. Aquí se genera el archivo de salida/ejecución del código realizado '.c', que será el que la máquina correrá y dará los resultados en 'output_addition-and-subtraction-of-matrices.txt'