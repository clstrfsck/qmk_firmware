#include "platform.h"

#include <stdint.h>
#include <stdlib.h>

#define LCG_A 16807
#define LCG_M 2147483647

#define LCG_Q (LCG_M / LCG_A)
#define LCG_R (LCG_M % LCG_A)

static int32_t lcg_seed = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
#pragma GCC diagnostic pop
  start();
  // Error if we get here
  return -1;
}

void finished(bool success) {
  // Stop the game task
  exit( success ? EXIT_SUCCESS : EXIT_FAILURE );
}

void init_random() {
  /* Nothing */
}

void set_random_seed(unsigned int seed) {
  lcg_seed = seed % LCG_M;
}

unsigned int get_random(unsigned int max) {
  if (lcg_seed == 0) {
    lcg_seed = 123459876;
  }
  /*
   * From "Random number generators: good ones are hard to find",
   * Park and Miller, Communications of the ACM, vol. 31, no. 10,
   * October 1988, p. 1195.
   */
  int32_t hi = lcg_seed / LCG_Q;
  int32_t lo = lcg_seed % LCG_Q;
  int32_t test = LCG_A * lo - LCG_R * hi;
  if (test > 0) {
    lcg_seed = test;
  } else {
    lcg_seed = test + LCG_M;
  }
  return lcg_seed % max; /* Not great, but good enough? */
}

int inchar() {
  return -1;
}

void outchar(int ch) {
  // Nothing
}
