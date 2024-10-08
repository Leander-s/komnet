#include "ping-pong.h"

int pingpong_root_run(int size, int messageSize, int verbose, int cycles) {
  char *recvBuffer = (char*)malloc(messageSize);
  char *sendBuffer = (char*)malloc(messageSize);
  int err;
  double sendTime, recvTime, rootDiff, nodeDiff, latencySum = 0;

  // Preparing buffer for send
  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL));

  for (int i = 0; i < cycles; i++) {
    // use sentTime/recvTime array for multiple nodes
    sendTime = MPI_Wtime();
    err = MPI_Send((void *)sendBuffer, messageSize, MPI_CHAR, 1, 1,
                   MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
      printf("Send error in root\n");
      return err;
    }
    err = MPI_Recv((void *)recvBuffer, messageSize, MPI_CHAR, 1, 1,
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    recvTime = MPI_Wtime();
    if (err != MPI_SUCCESS) {
      printf("Read error in root\n");
      return err;
    }

    err = MPI_Recv((void *)&nodeDiff, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
    if(err != MPI_SUCCESS){
        printf("Couldn't read recvTime!\n");
        return err;
    }

    rootDiff = recvTime - sendTime;
    latencySum += rootDiff;

    // Print what was read from node i.
    log_print(verbose, "Root: Received from other node : '%s'\n",
              (char *)recvBuffer);
  }

  double latency = latencySum / cycles;
  printf("Half-round-trip latency was %lf ms.\n", latency / 2 * 1000);

  free(sendBuffer);
  free(recvBuffer);
  return MPI_SUCCESS;
}

int pingpong_node_run(int rank, int messageSize, int verbose, int cycles) {
  char *recvBuffer = (char*)malloc(messageSize);
  char *sendBuffer = (char*)malloc(messageSize);
  int err;
  double sendTime, recvTime, diff;

  memset(recvBuffer, 0, messageSize);
  generate_random_message(sendBuffer, messageSize, time(NULL) + rank);

  for (int i = 0; i < cycles; i++) {
    sendTime = MPI_Wtime();
    err = MPI_Recv((void *)recvBuffer, messageSize, MPI_CHAR, 0, 1,
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (err != MPI_SUCCESS) {
      log_print(verbose, "Read error in %d\n", rank);
      return err;
    }

    // print what was read from root
    log_print(verbose, "Node %d: Received from root : '%s'\n", rank,
              (char *)recvBuffer);

    err = MPI_Send((void *)sendBuffer, messageSize, MPI_CHAR, 0, 1,
                   MPI_COMM_WORLD);
    recvTime = MPI_Wtime();
    if (err != MPI_SUCCESS) {
      printf("Send error in %d\n", rank);
      return err;
    }

    diff = recvTime - sendTime;

    err = MPI_Send((void*)&diff, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    if(err != MPI_SUCCESS){
        printf("Couldn't send recvTime!\n");
        return err;
    }
  }

  free(sendBuffer);
  free(recvBuffer);
  return MPI_SUCCESS;
}
