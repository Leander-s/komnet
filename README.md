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
maybe run tests program 5 times instead of doing for loop in test
Powerpoint
PDF
Why spikes at beginning sometimes
9.1 run scripts

Questions:
"Führen sie ihre Messungen fünf mal durch" - 5 MPI_Init-MPI_Finalize?

Tests:
half-round-trip:
    diagram

cpunodebind stuff:
    how does this work???
    diagram
