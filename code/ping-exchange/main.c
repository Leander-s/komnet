#include "ping-exchange.h"
#include "arg_util.h"

int main(int argc, char **argv) {
  // Init mpi
  MPI_Init(&argc, &argv);

  int messageSize = 16;
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
  handle_args(argc, argv, rank, &messageSize, &verbose, &cycles);

  // if root or node
  if (rank == 0) {
    err = ping_exchange_root_run(size, messageSize, verbose, cycles);
  } else {
    err = ping_exchange_node_run(rank, messageSize, verbose, cycles);
  }

  // Deinit mpi
  MPI_Finalize();
  return 0;
}
