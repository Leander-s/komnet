modules:
    mpi/OpenMPI

build:
    run build_t9.sh script

run:
    tests:
        run ./run_tests.sh <partition> (largemem by default)
        9.2 outputs in ./results_92
        9.3 outputs in ./results_93

TODO:
maybe run tests program 5 times instead of doing for loop in test
Powerpoint
PDF
Why spikes at beginning sometimes
Why spike at 2^17 message size?

Questions:
"Führen sie ihre Messungen fünf mal durch" - 5 MPI_Init-MPI_Finalize?
