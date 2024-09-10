#include "ping-exchange/ping-exchange.h"
#include "ping-pong/ping-pong.h"
#include "util.h"

#include "bundle_args.c"

int main(int argc, char **argv) {
  // Init mpi
  MPI_Init(&argc, &argv);

  int (*root_functions[2])(int a, int b, int c, int cycles);
  int (*node_functions[2])(int a, int b, int c, int cycles);
  root_functions[PING_PONG] = pingpong_root_run;
  root_functions[PING_EXCHANGE] = ping_exchange_root_run;
  node_functions[PING_PONG] = pingpong_node_run;
  node_functions[PING_EXCHANGE] = ping_exchange_node_run;

  int messageSize = 16;
  int mode = PING_PONG;
  int verbose = 0;
  int cycles = 5;

  // Get rank and size for this process
  int rank, size, err;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Checking the -mca components
  char *btl_value = getenv("OMPI_MCA_btl");
  if (btl_value != NULL) {
    root_print(rank, "OMPI_MCA_btl is set to: %s\n", btl_value);
  } else {
    root_print(rank, "OMPI_MCA_btl is not set\n");
  }

  // Handling arguments
  if(handle_args(argc, argv, rank, &messageSize, &mode, &verbose, &cycles)){
      // returning if arg was --help
      return 0;
  }

  // if root or node
  if (rank == 0) {
    err = root_functions[mode](size, messageSize, verbose, cycles);
  } else {
    err = node_functions[mode](rank, messageSize, verbose, cycles);
  }

  // Deinit mpi
  MPI_Finalize();
  return 0;
}
