#include "ping-exchange.h"
#include "util.h"
#include <math.h>
#include <unistd.h>

int run_test(int messageSize, int rank, int size) {
  int err;
  // if root or node
  if (rank == 0) {
    err = ping_exchange_root_run(size, messageSize, 0);
  } else {
    err = ping_exchange_node_run(rank, messageSize, 0);
  }
  return err;
}

int main(int argc, char **argv) {
  // Init mpi
  MPI_Init(&argc, &argv);

  int messageSize = 16;
  int verbose = 0;

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
  for (int i = 1; i < argc; i++) {
    // Checking -s arg for size
    if (strcmp(argv[i], "-s") == 0) {
      if (i + 1 >= argc) {
        root_print(
            rank,
            "Specify message size using '-s <size>'. Using default size:%d.\n",
            messageSize);
        continue;
      }
      messageSize = pow(2, string_to_int(argv[i + 1]));
      root_print(rank, "Using message size %d.\n", messageSize);
      i++;
      continue;
    }

    if (strcmp(argv[i], "-v") == 0) {
      verbose = 1;
      continue;
    }

    if (strcmp(argv[i], "--help") == 0) {
      root_print(
          rank,
          "Valid arguments are:\n-m <mode> : Specifies run mode. "
          "<mode> can be 'pp' or 'pe'\n-s <size> : Specifies message size. "
          "<size> is an integer.\n-v : Verbose -> prints messages.\n");
      MPI_Finalize();
      return 0;
    }

    // Arg not valid, skip
    root_print(
        rank,
        "Argument '%s' is not a valid argument.\nSkipping this "
        "argument.\nValid arguments are:\n-m <mode> : Specifies run mode. "
        "<mode> can be 'pp' or 'pe'\n-s <size> : Specifies message size. "
        "<size> is an integer.\n-v : Verbose -> prints messages.\n",
        argv[i]);
  }

  for (int i = 0; i <= 20; i++) {
    root_print(rank, "Results for 2^%d:\n", i);
    for (int j = 1; j <= 5; j++) {
      root_print(rank, "Result number %d: ", j);
      sleep(1);
      run_test(pow(2, i), rank, size);
    }
  }

  // Deinit mpi
  MPI_Finalize();
  return 0;
}
