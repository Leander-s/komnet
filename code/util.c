#include "util.h"

int string_to_int(char *str) {
  errno = 0;
  char *end;
  const long i = strtol(str, &end, 10);
  const int range_error = errno == ERANGE;
  return (int)(i);
}

void generate_random_message(char *buffer, int bufferSize, int seed) {
  // init rng
  /* random message
  srandom(seed);

  for (int i = 0; i < bufferSize; i++) {
    buffer[i] = random() % (91 - 33) + 33;
  }
  */

  // Just return a bunch of a (maybe less interference)
  memset(buffer, 'a', bufferSize);

  // Making sure we don't print the stack when verbose
  buffer[bufferSize - 1] = 0;
}

int root_print(int rank, const char *format, ...){
    if(rank != 0) return 0;
    int result;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    return result;
}

int log_print(int verbose, const char *format, ...){
    if(!verbose) return 0;
    int result;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    return result;
}
