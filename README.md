Scripts will only run with slurm and OpenMPI. build.sh loads mpi/OpenMPI module
automatically.

***
modules:<br/>
mpi/OpenMPI

***

build:<br/>
    
    ./build.sh

***

run:<br/>
    tests:<br/>

        ./run_tests.sh <partition><br/> 
(largemem by default)<br/>
9.2 outputs in ./results_92<br/>
9.3 outputs in ./results_93<br/>

Parameters are optional for Ping-Pong and Ping-Exchange<br/>
ping-pong:<br/>

        ./run_ping_pong.sh -s <size> -c <cycles><br/>
ping-exchange:<br/>

        ./run_ping_exchange.sh -s <size> -c <cycles><br/>

***

TODO:
maybe run tests program 5 times instead of doing for loop in test
Powerpoint
PDF
Why spikes at beginning sometimes
Why spike at 2<sup>17</sup> message size?

Questions:
"Führen sie ihre Messungen fünf mal durch" - 5 MPI_Init-MPI_Finalize?
