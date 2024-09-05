# all
mpicc main.c util.c ping-pong.c ping-exchange.c util.h ping-pong.h ping-exchange.h -o build/t9_bundle -lm

# each
mpicc ping-pong-main.c util.c ping-pong.c util.h ping-pong.h -o build/t9_pingpong -lm
mpicc ping-exchange-main.c util.c ping-exchange.c util.h ping-exchange.h -o build/t9_ping_exchange -lm

# tests
mpicc ping-pong-tests.c util.c ping-pong.c util.h ping-pong.h -o build/t9_pingpong_tests -lm
mpicc ping-exchange-tests.c util.c ping-exchange.c util.h ping-exchange.h -o build/t9_ping_exchange_tests -lm
