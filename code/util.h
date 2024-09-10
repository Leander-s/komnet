#include "config.h"

int string_to_int(char *str);
void generate_random_message(char *buffer, int bufferSize, int seed);
int root_print(int rank, const char *format, ...);
int log_print(int verbose, const char *format, ...);
