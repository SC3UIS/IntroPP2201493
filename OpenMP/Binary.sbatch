#!/bin/bash
#SBATCH --job-name=OMP_BinarySearch.c
#SBATCH --output=output_BinarySearch.txt
#SBATCH --ntasks=1    
#SBATCH --nodes=1   
#SBATCH --cpus-per-task=4    

gcc -fopenmp OMP_BinarySearch.c -o x_BinarySearch   
./x_BinarySearch