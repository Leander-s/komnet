#include <errno.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int string_to_int(char *str) {
  errno = 0;
  char *end;
  const long i = strtol(str, &end, 10);
  const int range_error = errno == ERANGE;
  return (int)(i);
}

void generate_random_message(char *buffer, int bufferSize, int seed) {
  // init rng
  srandom(seed);

  for (int i = 0; i < bufferSize; i++) {
    buffer[i] = random() % (91 - 33) + 33;
  }
}

int root_func(int size, int messageSize) {
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
    printf("Root: Received from node %d : '%s'\n", i, (char *)buffer);
  }
  free(buffer);
  return MPI_SUCCESS;
}

int other_func(int rank, int messageSize) {
  char *buffer = (char *)malloc(sizeof(char) * messageSize);
  int err;
  memset(buffer, 0, messageSize);
  err = MPI_Recv((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
  if (err != MPI_SUCCESS) {
    printf("Read error in %d\n", rank);
    free(buffer);
    return err;
  }

  // print what was read from root
  printf("Node %d: Received from root : '%s'\n", rank, (char *)buffer);

  memset(buffer, 0, messageSize);
  generate_random_message(buffer, messageSize, time(NULL)*rank);
  err = MPI_Send((void *)buffer, messageSize, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    printf("Send error in %d\n", rank);
    free(buffer);
    return err;
  }
  free(buffer);
  return MPI_SUCCESS;
}

int main(int argc, char **argv) {
  int err, rank, size, messageSize = 16;
  err = MPI_Init(&argc, &argv);
  if (err != 0) {
    printf("Error initializing MPI!\n");
    return 1;
  }

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-s") == 0) {
      if (i + 1 >= argc) {
        printf("Specify message size '-s <size>'. Using 16 by default.\n");
        continue;
      }
      messageSize = string_to_int(argv[i + 1]);
    }
  }

  err = MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (err != 0) {
    printf("Error getting number of processes!\n");
    return 1;
  }
  err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (err != 0) {
    printf("Error getting rank of process!\n");
    return 1;
  }
  if (rank == 0) {
    root_func(size, messageSize);
  } else {
    other_func(rank, messageSize);
  }
  MPI_Finalize();
  return 0;
}
