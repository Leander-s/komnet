#!/bin/bash
#SBATCH --job-name=pp_intranode_test
#SBATCH --partition=largemem
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --time=01:00:00
#SBATCH --output=./results_92/pp_intranode.out
#SBATCH --error=./errors_92/pp_intranode.err

mpirun --mca btl tcp,self -np 2 ./build/pingpong_tests
