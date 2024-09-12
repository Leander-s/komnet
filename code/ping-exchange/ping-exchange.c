#include "ping-exchange.h"

int ping_exchange_root_run(int size, int messageSize, int verbose, int cycles) {
  double sendTime, recvTime, rootDiff, nodeDiff, latencySum = 0;
  int err;
  char sendBuffer[messageSize];
  char recvBuffer[messageSize];
  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL));

  for (int i = 0; i < cycles; i++) {

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
    err = MPI_Recv(&nodeDiff, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
    if(err != MPI_SUCCESS){
        printf("Couldn't receive time!\n");
        return err;
    }

    rootDiff = recvTime - sendTime;

    // add the smaller difference onto latencySum
    latencySum += (rootDiff < nodeDiff) ? rootDiff : nodeDiff;

    // Print what was read from node i.
    log_print(verbose, "Root: Read '%s' from node %d.\n", (char *)recvBuffer,
              1);
  }

  double latency = latencySum / cycles;
  printf("Half-round-trip latency was %lf ms.\n", latency / 2 * 1000);

  return MPI_SUCCESS;
}

int ping_exchange_node_run(int rank, int messageSize, int verbose, int cycles) {
  int err;
  char recvBuffer[messageSize];
  char sendBuffer[messageSize];
  double sendTime, recvTime, diff;
  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL) + rank);
  for (int i = 0; i < cycles; i++) {
    sendTime = MPI_Wtime();
    err = MPI_Sendrecv((void*)sendBuffer, messageSize, MPI_CHAR, 0, 1, (void*)recvBuffer,
                       messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                       MPI_STATUS_IGNORE);
    recvTime = MPI_Wtime();
    if (err != MPI_SUCCESS) {
      printf("Read error in %d\n", rank);
      return err;
    }

    diff = recvTime - sendTime;

    err = MPI_Send(&diff, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    if(err != MPI_SUCCESS){
        printf("Couldn't send time!\n");
        return err;
    }

    // print what was read from root
    log_print(verbose, "Node %d: Read '%s' from root.\n", rank,
              (char *)recvBuffer);
  }

  return MPI_SUCCESS;
}
