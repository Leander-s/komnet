build:
    run build script

run:
    run srun --partition <partition> -N <N> -n <n> ./<any program in /build> <args>
    to get args run ./<any program in /build> --help

TODO:
test not working with tcp

Tests:
half-round-trip:
    ping-pong/ping-exchange, messageSize 2⁰ -> 2²⁰, intranode/internode
    5X
    diagram

cpunodebind stuff:
    half-round-trip using numactl --cpunodebind=(0|1)
    different? -> why
    diagram
