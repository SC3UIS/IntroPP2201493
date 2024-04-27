#!/bin/bash

#SBATCH -p normal
#SBATCH --ntasks=4
#SBATCH --output=output_postmansort_MPI.txt
#SBATCH --error=error_%j.txt
#SBATCH --cpus-per-task=1
#SBATCH -w guane10

module load devtools/mpi/openmpi/4.1.2

mpic++ -fopenmp MPI_PostmanSort.c -o X_MPI_PostmanSortO
mpirun -np 4 ./X_MPI_PostmanSortO
