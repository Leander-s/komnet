# all
mpicc main.c util.c ping-pong.c ping-exchange.c util.h ping-pong.h ping-exchange.h -o build/bundle -lm

# each
mpicc ping-pong-main.c util.c ping-pong.c util.h ping-pong.h -o build/pingpong -lm
mpicc ping-exchange-main.c util.c ping-exchange.c util.h ping-exchange.h -o build/ping_exchange -lm

# tests
mpicc ping-pong-tests.c util.c ping-pong.c util.h ping-pong.h -o build/pingpong_tests -lm
mpicc ping-exchange-tests.c util.c ping-exchange.c util.h ping-exchange.h -o build/ping_exchange_tests -lm
