Tests:
half-round-trip:
    ping-pong/ping-exchange, messageSize 2⁰ -> 2²⁰, intranode/internode
    5X

cpunodebind stuff:
    half-round-trip using numactl --cpunodebind=(0|1)
    different? -> why

