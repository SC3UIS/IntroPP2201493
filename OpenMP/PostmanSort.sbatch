#!/bin/bash
#SBATCH --job-name=OMP_PostmanSort.c
#SBATCH --output=output_PostmanSort.txt    
#SBATCH --ntasks=1    
#SBATCH --nodes=1   
#SBATCH --cpus-per-task=4    

gcc -fopenmp OMP_PostmanSort.c -o x_PostmanSort   
./x_PostmanSort