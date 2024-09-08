modules:
    mpi/OpenMPI

build:
    run build_t9.sh script

run:
    tests:
        run scripts
        outputs in ./results
        potential errors in ./errors 

TODO:
maybe run tests program 5 times instead of doing for loop in test
Powerpoint
PDF
Why spikes at beginning sometimes

Questions:
"Führen sie ihre Messungen fünf mal durch" - 5 MPI_Init-MPI_Finalize?

Tests:
half-round-trip:
    diagram

cpunodebind stuff:
    binds process to numanode in physical node process was distributed to
        why is numa node 7 slower than numa node 0???
    diagram
