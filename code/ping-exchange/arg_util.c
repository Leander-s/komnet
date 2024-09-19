#include "arg_util.h"

int handle_args(int argc, char **argv, int rank, int *messageSize, int *verbose,
                int *cycles) {
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

    if (strcmp(argv[i], "-v") == 0) {
      *verbose = 1;
      continue;
    }

    if (strcmp(argv[i], "-c") == 0) {
      if (i + 1 >= argc) {
        root_print(
            rank,
            "Specify cycles using '-c <cycles>'. Using default cycles: %d.\n",
            *cycles);
        continue;
      }
      *cycles = string_to_int(argv[i + 1]);
      root_print(rank, "Using %d cycles.\n", *cycles);
      i++;
      continue;
    }

    if (strcmp(argv[i], "--help") == 0) {
      root_print(
          rank,
          "Valid arguments are:\n-m <mode> : Specifies run mode. "
          "<mode> can be 'pp' or 'pe'\n-s <size> : Specifies message size. "
          "<size> is an integer.\n-v : Verbose -> prints messages.\n-c "
          "<cycles> : Specifies how often the message is sent and received.\n");
      MPI_Finalize();
      return 1;
    }

    // Arg not valid, skip
    root_print(
        rank,
        "Argument '%s' is not a valid argument.\nSkipping this "
        "argument.\nValid arguments are:\n"
        "-s <size> : Specifies message size. "
        "<size> is an integer.\n-v : Verbose -> prints messages.\n-c <cycles> "
        ": Specifies how often the message is sent and received.\n",
        argv[i]);
  }
  return 0;
}
