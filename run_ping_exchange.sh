#!/bin/bash

#SBATCH --job-name=ping_exchange
#SBATCH --partition=largemem
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --time=00:01:00
#SBATCH --output=./ping_exchange_out/pe.out
#SBATCH --error=./ping_exchange_err/pe.err

sbatch mpirun -np 2 -mca btl tcp,self ./build/ping_exchange
