modules:
    mpi/OpenMPI

build:
    run build_t9.sh script

run:
    tests:
        run scripts
        outputs in ./results
        potential errors in ./errors 

    run srun --partition <partition> -N <N> -n <n> ./<any program in /build> <args>
    to get args run ./<any program in /build> --help

TODO:
Why spikes at beginning sometimes
9.1 run scripts

Tests:
half-round-trip:
    diagram

cpunodebind stuff:
    different? -> no -> how? 
    diagram
