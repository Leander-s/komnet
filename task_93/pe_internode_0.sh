#!/bin/bash
#SBATCH --job-name=pe_internode_test
#SBATCH --partition=largemem
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=01:00:00
#SBATCH --output=./results_93/pe_internode_0.out
#SBATCH --error=./errors_93/pe_internode_0.err

mpirun --mca btl tcp,self -np 2 numactl --cpunodebind=0 ./build/ping_exchange_tests
