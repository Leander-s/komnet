#include <errno.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_to_int(char *str);
void generate_random_message(char *buffer, int bufferSize, int seed);
