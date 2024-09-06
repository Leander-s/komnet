modules:
    mpi/OpenMPI

build:
    run build_t9.sh script

run:
  tests:
    run scripts

    run srun --partition <partition> -N <N> -n <n> ./<any program in /build> <args>
    to get args run ./<any program in /build> --help

TODO:
need to use srun with -mca btl tcp,self
update run scripts

9.1 run scripts

Tests:
half-round-trip:
    diagram

cpunodebind stuff:
    different? -> no -> how? 
    diagram
