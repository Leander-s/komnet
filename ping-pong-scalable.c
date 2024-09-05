#include "ping-pong.h"
#include <mpi.h>

int pingpong_root_run(int size, int messageSize, int verbose) {
  char buffer[messageSize];
  // use sentTime/recvTime array for multiple nodes
  double sendTime, recvTime, latency;
  int err;

  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL));
  for (int i = 1; i < size; i++) {
    sendTime = MPI_Wtime();

    log_print(1, "root sending..\n");

    err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, i, 1, MPI_COMM_WORLD);

    log_print(1, "root sent..\n");

    if (err != MPI_SUCCESS) {
      printf("Send error in root\n");
      return err;
    }
  }
  memset(buffer, 0, messageSize);
  for (int i = 1; i < size; i++) {

    log_print(1, "root receiving..\n");

    err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, i, 1, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);

    log_print(1, "root received..\n");

    recvTime = MPI_Wtime();
    if (err != MPI_SUCCESS) {
      printf("Read error in root\n");
      return err;
    }

    latency = recvTime - sendTime;

    // Print what was read from node i.
    log_print(verbose, "Root: Received from node %d : '%s'\n", i,
              (char *)buffer);
  }

  printf("Half-round-trip latency : %lf ms.\n", latency / 2 * 1000);
  return MPI_SUCCESS;
}

int pingpong_node_run(int rank, int messageSize, int verbose) {
  char buffer[messageSize];
  int err;

  memset(buffer, 0, messageSize);

  log_print(1, "node receiving..\n");

  err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

  log_print(1, "node received..\n");

  if (err != MPI_SUCCESS) {
    log_print(verbose, "Read error in %d\n", rank);
    return err;
  }

  // print what was read from root
  log_print(verbose, "Node %d: Received from root : '%s'\n", rank,
            (char *)buffer);

  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL) + rank);

  log_print(1, "node sending..\n");

  err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD);

  log_print(1, "node sent..\n");

  if (err != MPI_SUCCESS) {
    printf("Send error in %d\n", rank);
    return err;
  }
  return MPI_SUCCESS;
}
