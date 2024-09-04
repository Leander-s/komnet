#include "ping-exchange.h"

int ping_exchange_root_run(int size, int messageSize, int verbose) {
  char sendBuffer[messageSize];
  char recvBuffer[messageSize];
  memset(sendBuffer, 0, messageSize);
  memset(recvBuffer, 0, messageSize);
  int err;
  sprintf(sendBuffer, "Hello from root");
  for (int i = 1; i < size; i++) {
    err =
        MPI_Sendrecv((void *)sendBuffer, messageSize, MPI_CHAR, i, 1, (void *)recvBuffer,
                     messageSize, MPI_CHAR, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      char errorString[64];
      int errorStringLength;
      MPI_Error_string(err, errorString, &errorStringLength);
      printf("Send error in root:%s\n", errorString);
      return err;
    }

    // Print what was read from node i.
    log(verbose,"Root: Read '%s' from node %d.\n", (char *)recvBuffer, i);
  }
  return MPI_SUCCESS;
}

int ping_exchange_node_run(int rank, int messageSize, int verbose) {
  char buffer[messageSize];
  memset(buffer, 0, messageSize);
  int err;
  err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
  if (err != MPI_SUCCESS) {
    printf("Read error in %d\n", rank);
    return err;
  }

  // print what was read from root
  log(verbose, "Node %d: Read '%s' from root.\n", rank, (char *)buffer);

  memset(buffer, 0, messageSize);
  sprintf(buffer, "Hello from %d", rank);
  err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    printf("Send error in %d\n", rank);
    return err;
  }
  return MPI_SUCCESS;
}
