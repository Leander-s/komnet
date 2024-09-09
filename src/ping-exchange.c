#include "ping-exchange.h"
#include <mpi.h>

int ping_exchange_root_run(int size, int messageSize, int verbose) {
  double latencySum = 0;
  int err, cycles = 100;
  char sendBuffer[messageSize];
  char recvBuffer[messageSize];
  memset(sendBuffer, 0, messageSize);
  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL));

  for (int i = 0; i < cycles; i++) {
    double sendTime, recvTime, latency;

    sendTime = MPI_Wtime();
    err = MPI_Sendrecv((void *)sendBuffer, messageSize, MPI_CHAR, 1, 1,
                       (void *)recvBuffer, messageSize, MPI_CHAR, 1, 1,
                       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    recvTime = MPI_Wtime();
    if (err != MPI_SUCCESS) {
      char errorString[64];
      int errorStringLength;
      MPI_Error_string(err, errorString, &errorStringLength);
      printf("Send error in root:%s\n", errorString);
      return err;
    }

    latency = recvTime - sendTime;
    latencySum += latency;

    // Print what was read from node i.
    log_print(verbose, "Root: Read '%s' from node %d.\n", (char *)recvBuffer,
              1);
  }

  double latency = latencySum / cycles;
  printf("Half-round-trip latency was %lf ms.\n", latency / 2 * 1000);

  return MPI_SUCCESS;
}

int ping_exchange_node_run(int rank, int messageSize, int verbose) {
  int err, cycles = 100;
  char recvBuffer[messageSize];
  char sendBuffer[messageSize];
  memset(sendBuffer, 0, messageSize);
  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL) + rank);
  for (int i = 0; i < cycles; i++) {
    err = MPI_Sendrecv(sendBuffer, messageSize, MPI_CHAR, 0, 1, recvBuffer,
                       messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                       MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      printf("Read error in %d\n", rank);
      return err;
    }

    // print what was read from root
    log_print(verbose, "Node %d: Read '%s' from root.\n", rank,
              (char *)recvBuffer);
  }

  return MPI_SUCCESS;
}
