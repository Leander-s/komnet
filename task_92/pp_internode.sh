#!/bin/bash
#SBATCH --job-name=pp_internode_test
#SBATCH --partition=largemem
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=01:00:00
#SBATCH --output=./results_92/pp_internode.out
#SBATCH --error=./errors_92/pp_internode.err

mpirun --mca btl tcp,self -np 2 ./build/pingpong_tests
