Scripts will only run with slurm and OpenMPI. build.sh loads mpi/OpenMPI module
automatically.

***
**Modules**<br/>
mpi/OpenMPI

***

**Build**<br/>
    
    ./build.sh

***

**Run**<br/>

Parameters are always optional<br/>

***

tests:<br/>

    ./run_tests.sh <partition>
    ./run_tests_async.sh <partition> (recommended)
<partition> is largemem by default<br/>
9.2 outputs in ./results_92<br/>
9.3 outputs in ./results_93<br/>

run_tests_async.sh runs all tests in the background. Much faster

***
Defaults are:<br/>
size = 10 (2<sup>10</sup>)<br/>
cycles = 5<br/>
partition = largemem<br/>

ping-pong:<br/>

    ./run_ping_pong.sh -s <size> -c <cycles> -p <partition>
ping-exchange:<br/>

    ./run_ping_exchange.sh -s <size> -c <cycles> -p <partition>


<!-- This is commented --> 
<!--
TODO:
maybe run tests program 5 times instead of doing for loop in test
Powerpoint
PDF
Why spikes at beginning sometimes
Why spike at 2<sup>17</sup> message size?

Questions:
"Führen sie ihre Messungen fünf mal durch" - 5 MPI_Init-MPI_Finalize?
-->
