#!/bin/bash
#SBATCH --job-name=pp_internode_test
#SBATCH --partition=largemem
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=01:00:00
#SBATCH --output=./results_93/pp_internode_0.out
#SBATCH --error=./errors_93/pp_internode_0.err

mpirun --mca btl tcp,self -np 2 numactl --cpunodebind=0 ./build/pingpong_tests
