# all
mpicc src/main.c src/util.c src/ping-pong.c src/ping-exchange.c src/util.h src/ping-pong.h src/ping-exchange.h -o build/bundle -lm

# each
mpicc src/ping-pong-main.c src/util.c src/ping-pong.c src/util.h src/ping-pong.h -o build/pingpong -lm
mpicc src/ping-exchange-main.c src/util.c src/ping-exchange.c src/util.h src/ping-exchange.h -o build/ping_exchange -lm

# tests
mpicc src/ping-pong-tests.c src/util.c src/ping-pong.c src/util.h src/ping-pong.h -o build/pingpong_tests -lm
mpicc src/ping-exchange-tests.c src/util.c src/ping-exchange.c src/util.h src/ping-exchange.h -o build/ping_exchange_tests -lm
