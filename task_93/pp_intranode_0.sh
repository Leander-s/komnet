#!/bin/bash
#SBATCH --job-name=pp_intranode_test
#SBATCH --partition=largemem
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --time=01:00:00
#SBATCH --output=./results_93/pp_intranode_0.out
#SBATCH --error=./errors_93/pp_intranode_0.err

mpirun --mca btl tcp,self -np 2 numactl --cpunodebind=0 ./build/pingpong_tests
