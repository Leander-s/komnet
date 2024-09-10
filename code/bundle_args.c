#include "util.h"

int handle_args(int argc, char **argv, int rank, int *messageSize, int *mode, int *verbose, int *cycles){
  for (int i = 1; i < argc; i++) {
    // Checking -s arg for size
    if (strcmp(argv[i], "-s") == 0) {
      if (i + 1 >= argc) {
        root_print(
            rank,
            "Specify message size using '-s <size>'. Using default size:%d.\n",
            *messageSize);
        continue;
      }
      *messageSize = pow(2, string_to_int(argv[i + 1]));
      root_print(rank, "Using message size %d.\n", *messageSize);
      i++;
      continue;
    }

    // Checking -c arg for cycles
    if (strcmp(argv[i], "-c") == 0) {
      if (i + 1 >= argc) {
        root_print(
            rank,
            "Specify cycles using '-c <cycles>'. Using default cycles:%d.\n",
            *cycles);
        continue;
      }
      *cycles = string_to_int(argv[i + 1]);
      root_print(rank, "Using cycles %d.\n", cycles);
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
        *mode = PING_EXCHANGE;
        i++;
        continue;
      } else {
        root_print(
            rank, "Invalid argument for '-m'. Using default mode ping-pong.\n");
        *mode = PING_PONG;
        i++;
        continue;
      }
    }

    if (strcmp(argv[i], "-v") == 0) {
      *verbose = 1;
      continue;
    }

    if (strcmp(argv[i], "--help") == 0) {
      root_print(
          rank,
          "Valid arguments are:\n-m <mode> : Specifies run mode. "
          "<mode> can be 'pp' or 'pe'\n-s <size> : Specifies message size. "
          "<size> is an integer.\n-v : Verbose -> prints messages.\n-c <cycles> : Specifies how often the message is sent and received.\n");
      MPI_Finalize();
      return 1;
    }

    // Arg not valid, skip
    root_print(
        rank,
        "Argument '%s' is not a valid argument.\nSkipping this "
        "argument.\nValid arguments are:\n-m <mode> : Specifies run mode. "
        "<mode> can be 'pp' or 'pe'\n-s <size> : Specifies message size. "
        "<size> is an integer.\n-v : Verbose -> prints messages.\n-c <cycles> : Specifies how often the message is sent and received.\n",
        argv[i]);
  }
  return 0;
}
