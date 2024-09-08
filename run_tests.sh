#!/bin/bash

export OMPI_MCA_btl=tcp,self

# task 9.2
srun --partition largemem -N 2 -n 2 ./build/ping_exchange_tests > ./results_92/pe_inter.out &
srun --partition largemem -N 1 -n 2 ./build/ping_exchange_tests > ./results_92/pe_intra.out &
srun --partition largemem -N 2 -n 2 ./build/pingpong_tests > ./results_92/pp_inter.out &
srun --partition largemem -N 1 -n 2 ./build/pingpong_tests > ./results_92/pp_intra.out &

# task 9.3
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=0 ./build/ping_exchange_tests > ./results_93/pe_inter_0.out & 
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=0 ./build/ping_exchange_tests > ./results_93/pe_intra_0.out &
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=7 ./build/ping_exchange_tests > ./results_93/pe_inter_7.out &
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=7 ./build/ping_exchange_tests > ./results_93/pe_intra_7.out &
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=0 ./build/pingpong_tests > ./results_93/pp_inter_0.out &
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=0 ./build/pingpong_tests > ./results_93/pp_intra_0.out &
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=7 ./build/pingpong_tests > ./results_93/pp_inter_7.out &
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=7 ./build/pingpong_tests > ./results_93/pp_intra_7.out &
