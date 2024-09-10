#include <errno.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int string_to_int(char *str);
void generate_random_message(char *buffer, int bufferSize, int seed);
int root_print(int rank, const char *format, ...);
int log_print(int verbose, const char *format, ...);
