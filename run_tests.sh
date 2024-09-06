#!/bin/bash

export OMPI_MCA_btl=tcp,self

# task 9.2
srun --partition largemem -N 2 -n 2 ./build/ping_exchange_tests
srun --partition largemem -N 1 -n 2 ./build/ping_exchange_tests
srun --partition largemem -N 2 -n 2 ./build/pingpong_tests
srun --partition largemem -N 1 -n 2 ./build/pingpong_tests

# task 9.3
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=0 ./build/ping_exchange_tests
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=0 ./build/ping_exchange_tests
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=1 ./build/ping_exchange_tests
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=1 ./build/ping_exchange_tests
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=0 ./build/pingpong_tests
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=0 ./build/pingpong_tests
srun --partition largemem -N 2 -n 2 numactl --cpunodebind=1 ./build/pingpong_tests
srun --partition largemem -N 1 -n 2 numactl --cpunodebind=1 ./build/pingpong_tests
