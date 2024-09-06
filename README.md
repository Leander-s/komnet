modules:
    mpi/OpenMPI

build:
    run build script

run:
    tests:
        run scripts
        outputs in ./results
        potential errors in ./errors 

    run srun --partition <partition> -N <N> -n <n> ./<any program in /build> <args>
    to get args run ./<any program in /build> --help

TODO:
Why spikes at beginning sometimes

Tests:
half-round-trip:
    diagram

cpunodebind stuff:
    half-round-trip using numactl --cpunodebind=(0|1)
    different? -> why
    diagram
