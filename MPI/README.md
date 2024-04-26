# Integrantes
* Luis Andres Gonzalez Corzo - 2201493
* Darien Andres Castañeda Agudelo - 2201922

## Binary Search
Este código presenta dos funciones principales: bubble_sort y binary_search. La primera ordena una lista de números utilizando el algoritmo de ordenamiento de burbuja. Este algoritmo recorre la lista varias veces, comparando elementos adyacentes y realizando intercambios si están desordenados. Este proceso continúa hasta que no se necesiten más intercambios, lo que indica que la lista está ordenada de manera ascendente.

Por otro lado, binary_search busca un valor específico en una lista ordenada utilizando el algoritmo de búsqueda binaria. Este algoritmo divide repetidamente la lista por la mitad y compara el valor buscado con el elemento en el medio. Si el valor buscado es igual al elemento medio, se devuelve como encontrado. Si es menor, la búsqueda se realiza en la mitad inferior de la lista; si es mayor, en la mitad superior. Este proceso se repite hasta que se encuentra el valor buscado o hasta que la lista se reduce a cero, indicando que el valor no está presente en la lista.

Para ejecutar el algoritmo pedimos una reserva interactiva:

```
srun -n 4 --pty /bin/bash
```
Luego cargamos el modulo de MPI:
```
module load devtools/mpi/openmpi/4.1.2 
```
* Compilamos el codigo usando: ```mpic++ -fopenmp MPI_BinarySearch.c -o X_MPI_BinarySearch```
Aqui despues de -fopenmp agregamos respectivas etiquetas de compilacion, se usaron -O, -O1 y -O3
* Lo ejecutamos usando: ```mpirun -np 4 ./X_MPI_BinarySearch```
### Tiempos con la etiqueta O:
![O0](/MPI/imagenes/BO.png)
### Tiempos con la etiqueta O1:
![O1](/MPI/imagenes/BO1.png)
### Tiempos con la etiqueta O3:
![O3](/MPI/imagenes/BO3.png)
