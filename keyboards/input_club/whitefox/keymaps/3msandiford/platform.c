#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "platform.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
#pragma GCC diagnostic pop
  start();
  // Error if we get here
  return -1;
}

void finished(bool success) {
  exit(success ? EXIT_SUCCESS : EXIT_FAILURE);
}

void init_random() {
  set_random_seed((unsigned int) time(NULL));
}

void set_random_seed(unsigned int seed) {
  srand(seed);
}

unsigned int get_random(unsigned int max) {
  return rand() % max; /* Not great, but good enough? */
}

int inchar() {
  return getchar();
}

void outchar(int ch) {
  putchar(ch);
}
