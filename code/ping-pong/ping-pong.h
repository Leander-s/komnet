#include "../util.h"
#include <math.h>
#include <mpi.h>
#include <time.h>

int pingpong_root_run(int size, int messageSize, int verbose, int cycles);
int pingpong_node_run(int rank, int messageSize, int verbose, int cycles);
