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
  srandom(seed);

  for (int i = 0; i < bufferSize; i++) {
    buffer[i] = random() % (91 - 33) + 33;
  }
}
