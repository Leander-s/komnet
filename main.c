#include "ping-exchange.h"
#include "ping-pong.h"
#include "util.h"
#include <math.h>

#define PING_PONG 0
#define PING_EXCHANGE 1

int main(int argc, char **argv) {
  // Init mpi
  MPI_Init(&argc, &argv);

  int (*root_functions[2])(int a, int b, int c);
  int (*node_functions[2])(int a, int b, int c);
  root_functions[PING_PONG] = pingpong_root_run;
  root_functions[PING_EXCHANGE] = ping_exchange_root_run;
  node_functions[PING_PONG] = pingpong_node_run;
  node_functions[PING_EXCHANGE] = ping_exchange_node_run;

  int messageSize = 16;
  int mode = PING_PONG;
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

    // Checking -m arg for modes
    if (strcmp(argv[i], "-m") == 0) {
      if (i + 1 >= argc) {
        root_print(rank,
                   "Specify mode using '-m <mode>'.\npp for ping-pong, pe for "
                   "ping-exchange.\nUsing default mode ping-pong.\n");
        continue;
      }
      if (strcmp(argv[i + 1], "pp") == 0) {
        mode = PING_PONG;
        i++;
        continue;
      } else if (strcmp(argv[i + 1], "pe") == 0) {
        mode = PING_EXCHANGE;
        i++;
        continue;
      } else {
        root_print(
            rank, "Invalid argument for '-m'. Using default mode ping-pong.\n");
        mode = PING_PONG;
        i++;
        continue;
      }
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

  // if root or node
  if (rank == 0) {
    err = root_functions[mode](size, messageSize, verbose);
  } else {
    err = node_functions[mode](rank, messageSize, verbose);
  }

  // Deinit mpi
  MPI_Finalize();
  return 0;
}
