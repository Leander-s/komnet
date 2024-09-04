#include "ping-pong.h"

int pingpong_root_run(int size, int messageSize, int verbose) {
  // technically sizof(char) = 1 but this gets the point across better
  char *buffer = (char *)malloc(sizeof(char) * messageSize);
  int err;

  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL));
  for (int i = 1; i < size; i++) {
    err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, i, 1, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
      printf("Send error in root\n");
      free(buffer);
      return err;
    }
  }
  memset(buffer, 0, messageSize);
  for (int i = 1; i < size; i++) {
    err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, i, 1, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      printf("Read error in root\n");
      free(buffer);
      return err;
    }

    // Print what was read from node i.
    log_print(verbose, "Root: Received from node %d : '%s'\n", i, (char *)buffer);
  }
  free(buffer);
  return MPI_SUCCESS;
}

int pingpong_node_run(int rank, int messageSize, int verbose) {
  char *buffer = (char *)malloc(sizeof(char) * messageSize);
  int err;
  memset(buffer, 0, messageSize);
  err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
  if (err != MPI_SUCCESS) {
    log_print(verbose, "Read error in %d\n", rank);
    free(buffer);
    return err;
  }

  // print what was read from root
  log_print(verbose, "Node %d: Received from root : '%s'\n", rank, (char *)buffer);

  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL) * rank);
  err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    printf("Send error in %d\n", rank);
    free(buffer);
    return err;
  }
  free(buffer);
  return MPI_SUCCESS;
}
