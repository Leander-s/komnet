#include <mpi.h>
#include <stdio.h>
#include <string.h>

int root_func(int size) {
  char buffer[32];
  memset(buffer, 0, 32);
  int err;
  sprintf(buffer, "Hello from root");
  for (int i = 1; i < size; i++) {
    err = MPI_Send((void*)buffer, 32, MPI_CHAR, i, 1, MPI_COMM_WORLD);
    if(err != MPI_SUCCESS){
        printf("Send error in root\n");
        return err;
    }
  }
  memset(buffer, 0, 32);
  for(int i = 1; i < size; i++){
      err = MPI_Recv((void*)buffer, 32, MPI_CHAR, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if(err != MPI_SUCCESS){
          printf("Read error in root\n");
          return err;
      }

      // Print what was read from node i.
      printf("Root: Read '%s' from node %d.\n", (char*)buffer, i);
  }
  return MPI_SUCCESS;
}

int other_func(int rank) {
  char buffer[32];
  memset(buffer, 0, 32);
  int err;
  err = MPI_Recv((void *)buffer, 32, MPI_CHAR, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
  if (err != MPI_SUCCESS) {
    printf("Read error in %d\n", rank);
    return err;
  }

  // print what was read from root
  printf("Node %d: Read '%s' from root.\n", rank, (char*)buffer);

  memset(buffer, 0, 32);
  sprintf(buffer, "Hello from %d", rank);
  err = MPI_Send((void *)buffer, 32, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    printf("Send error in %d\n", rank);
    return err;
  }
  return MPI_SUCCESS;
}

int main(int argc, char **argv) {
  int err, rank, size;
  err = MPI_Init(&argc, &argv);
  if (err != 0) {
    printf("Error initializing MPI!\n");
    return 1;
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
  printf("Rank : %d of %d\n", rank, size);
  if(rank == 0){
      root_func(size);
  }else{
      other_func(rank);
  }
  MPI_Finalize();
  return 0;
}
