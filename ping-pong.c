#include "ping-pong.h"
#include <mpi.h>

int pingpong_root_run(int size, int messageSize, int verbose) {
  char buffer[messageSize];

  // use sentTime/recvTime array for multiple nodes
  double sendTime, recvTime, latency;
  int err;

  // Preparing buffer for send
  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL));
  sendTime = MPI_Wtime();
  err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    printf("Send error in root\n");
    return err;
  }
  memset(buffer, 0, messageSize);
  err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, 1, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
  recvTime = MPI_Wtime();
  if (err != MPI_SUCCESS) {
    printf("Read error in root\n");
    return err;
  }

  latency = recvTime - sendTime;

  // Print what was read from node i.
  log_print(verbose, "Root: Received from other node : '%s'\n",  (char *)buffer);

  printf("Half-round-trip latency : %lf ms.\n", latency / 2 * 1000);
  return MPI_SUCCESS;
}

int pingpong_node_run(int rank, int messageSize, int verbose) {
  char buffer[messageSize];
  int err;

  memset(buffer, 0, messageSize);
  err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
  if (err != MPI_SUCCESS) {
    log_print(verbose, "Read error in %d\n", rank);
    return err;
  }

  // print what was read from root
  log_print(verbose, "Node %d: Received from root : '%s'\n", rank,
            (char *)buffer);

  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL) + rank);
  err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    printf("Send error in %d\n", rank);
    return err;
  }
  return MPI_SUCCESS;
}
