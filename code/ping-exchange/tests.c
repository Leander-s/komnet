#include "ping-exchange.h"
#include <unistd.h>

int run_test(int messageSize, int rank, int size) {
  int err;
  // if root or node
  if (rank == 0) {
    err = ping_exchange_root_run(size, messageSize, 0, 100);
  } else {
    err = ping_exchange_node_run(rank, messageSize, 0, 100);
  }
  return err;
}

int main(int argc, char **argv) {
  // Init mpi
  MPI_Init(&argc, &argv);

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

  for (int i = 0; i <= 20; i++) {
    root_print(rank, "Results for 2^%d:\n", i);
    for (int j = 1; j <= 5; j++) {
      root_print(rank, "Result number %d: ", j);
      run_test(pow(2, i), rank, size);
    }
  }

  // Deinit mpi
  MPI_Finalize();
  return 0;
}
