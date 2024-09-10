#include "ping-pong.h"

int pingpong_root_run(int size, int messageSize, int verbose, int cycles) {
  char recvBuffer[messageSize];
  char sendBuffer[messageSize];
  int err;
  double latencySum = 0;

  // Preparing buffer for send
  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL));

  for (int i = 0; i < cycles; i++) {
    // use sentTime/recvTime array for multiple nodes
    double sendTime, recvTime, latency;
    sendTime = MPI_Wtime();
    err = MPI_Send((void *)sendBuffer, messageSize, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
      printf("Send error in root\n");
      return err;
    }
    err = MPI_Recv((void *)recvBuffer, messageSize, MPI_CHAR, 1, 1, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
    recvTime = MPI_Wtime();
    if (err != MPI_SUCCESS) {
      printf("Read error in root\n");
      return err;
    }

    latency = recvTime - sendTime;
    latencySum += latency;

    // Print what was read from node i.
    log_print(verbose, "Root: Received from other node : '%s'\n",
              (char *)recvBuffer);
  }

  double latency = latencySum / cycles;
  printf("Half-round-trip latency was %lf ms.\n", latency / 2 * 1000);
  return MPI_SUCCESS;
}

int pingpong_node_run(int rank, int messageSize, int verbose, int cycles) {
  char recvBuffer[messageSize];
  char sendBuffer[messageSize];
  int err;

  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL) + rank);

  for (int i = 0; i < cycles; i++) {
    err = MPI_Recv((void *)recvBuffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      log_print(verbose, "Read error in %d\n", rank);
      return err;
    }

    // print what was read from root
    log_print(verbose, "Node %d: Received from root : '%s'\n", rank,
              (char *)recvBuffer);
    memset(recvBuffer, 0, messageSize);

    err = MPI_Send((void *)sendBuffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
      printf("Send error in %d\n", rank);
      return err;
    }
  }

  return MPI_SUCCESS;
}
