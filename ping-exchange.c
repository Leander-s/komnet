#include "ping-exchange.h"
#include <mpi.h>

int ping_exchange_root_run(int size, int messageSize, int verbose) {
  char sendBuffer[messageSize];
  char recvBuffer[messageSize];
  memset(sendBuffer, 0, messageSize);
  memset(recvBuffer, 0, messageSize);
  int err;
  sprintf(sendBuffer, "Hello from root");
  for (int i = 1; i < size; i++) {
    err = MPI_Sendrecv((void *)sendBuffer, messageSize, MPI_CHAR, i, 1,
                       (void *)recvBuffer, messageSize, MPI_CHAR, i, 1,
                       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      char errorString[64];
      int errorStringLength;
      MPI_Error_string(err, errorString, &errorStringLength);
      printf("Send error in root:%s\n", errorString);
      return err;
    }

    // Print what was read from node i.
    log_print(verbose, "Root: Read '%s' from node %d.\n", (char *)recvBuffer,
              i);
  }
  return MPI_SUCCESS;
}

int ping_exchange_node_run(int rank, int messageSize, int verbose) {
  char recvBuffer[messageSize];
  char sendBuffer[messageSize];
  memset(sendBuffer, 0, messageSize);
  memset(recvBuffer, 0, messageSize);
  sprintf(sendBuffer, "Hello from %d", rank);
  int err;
  err = MPI_Sendrecv(sendBuffer, messageSize, MPI_CHAR, 0, 1, recvBuffer,
                     messageSize, MPI_CHAR, rank, 1, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
  if (err != MPI_SUCCESS) {
    printf("Read error in %d\n", rank);
    return err;
  }

  // print what was read from root
  log_print(verbose, "Node %d: Read '%s' from root.\n", rank,
            (char *)recvBuffer);

  return MPI_SUCCESS;
}
