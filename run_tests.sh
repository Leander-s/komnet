#!/bin/bash

if [ $# -eq 0 ]; then
	part=largemem
else
	part=$1
fi

echo "Running on ${part}"

rm ./results_*/*

export OMPI_MCA_btl=

echo -ne '[                    ]\r'
# infiniband
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 ./build/ping_exchange_tests > ./results_infiniband/ib_pe_inter.out
echo -ne '[#                   ]\r'
srun --partition $part -N 1 -n 2 ./build/ping_exchange_tests > ./results_infiniband/ib_pe_intra.out
echo -ne '[##                  ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 ./build/pingpong_tests > ./results_infiniband/ib_pp_inter.out
echo -ne '[###                 ]\r'
srun --partition $part -N 1 -n 2 ./build/pingpong_tests > ./results_infiniband/ib_pp_intra.out
echo -ne '[####                ]\r'

export OMPI_MCA_btl=tcp,self

# task 9.2
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 ./build/ping_exchange_tests > ./results_92/pe_inter.out
echo -ne '[#####               ]\r'
srun --partition $part -N 1 -n 2 ./build/ping_exchange_tests > ./results_92/pe_intra.out
echo -ne '[######              ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 ./build/pingpong_tests > ./results_92/pp_inter.out
echo -ne '[#######             ]\r'
srun --partition $part -N 1 -n 2 ./build/pingpong_tests > ./results_92/pp_intra.out
echo -ne '[########            ]\r'

# task 9.3
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 numactl --cpunodebind=0 ./build/ping_exchange_tests > ./results_93/pe_inter_0.out 
echo -ne '[#########           ]\r'
srun --partition $part -N 1 -n 2 numactl --cpunodebind=0 ./build/ping_exchange_tests > ./results_93/pe_intra_0.out
echo -ne '[##########          ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 numactl --cpunodebind=7 ./build/ping_exchange_tests > ./results_93/pe_inter_7.out
echo -ne '[###########         ]\r'
srun --partition $part -N 1 -n 2 numactl --cpunodebind=7 ./build/ping_exchange_tests > ./results_93/pe_intra_7.out
echo -ne '[############        ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 numactl --cpunodebind=1 ./build/ping_exchange_tests > ./results_93/pe_inter_1.out
echo -ne '[#############       ]\r'
srun --partition $part -N 1 -n 2 numactl --cpunodebind=1 ./build/ping_exchange_tests > ./results_93/pe_intra_1.out
echo -ne '[##############      ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 numactl --cpunodebind=0 ./build/pingpong_tests > ./results_93/pp_inter_0.out
echo -ne '[###############     ]\r'
srun --partition $part -N 1 -n 2 numactl --cpunodebind=0 ./build/pingpong_tests > ./results_93/pp_intra_0.out
echo -ne '[################    ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 numactl --cpunodebind=7 ./build/pingpong_tests > ./results_93/pp_inter_7.out
echo -ne '[#################   ]\r'
srun --partition $part -N 1 -n 2 numactl --cpunodebind=7 ./build/pingpong_tests > ./results_93/pp_intra_7.out
echo -ne '[##################  ]\r'
srun --partition $part -N 2 -n 2 --ntasks-per-node=1 numactl --cpunodebind=1 ./build/pingpong_tests > ./results_93/pp_inter_1.out
echo -ne '[################### ]\r'
srun --partition $part -N 1 -n 2 numactl --cpunodebind=1 ./build/pingpong_tests > ./results_93/pp_intra_1.out
echo -ne '[####################]\r'
