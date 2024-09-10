if [ ! -d "build" ]; then
    mkdir "build"
    echo "build created"
fi

module load mpi/OpenMPI

# all
mpicc code/main.c code/bundle_args.c code/util.c code/ping-pong/ping-pong.c code/ping-exchange/ping-exchange.c code/config.h code/util.h code/ping-pong/ping-pong.h code/ping-exchange/ping-exchange.h -o build/bundle -lm

# each
mpicc code/ping-pong/main.c code/ping-pong/arg_util.c code/util.c code/ping-pong/ping-pong.c code/util.h code/ping-pong/ping-pong.h -o build/pingpong -lm
mpicc code/ping-exchange/main.c code/ping-exchange/arg_util.c code/util.c code/ping-exchange/ping-exchange.c code/util.h code/ping-exchange/ping-exchange.h -o build/ping_exchange -lm

# tests
mpicc code/ping-pong/tests.c code/util.c code/ping-pong/ping-pong.c code/util.h code/ping-pong/ping-pong.h -o build/pingpong_tests -lm
mpicc code/ping-exchange/tests.c code/util.c code/ping-exchange/ping-exchange.c code/util.h code/ping-exchange/ping-exchange.h -o build/ping_exchange_tests -lm
