#include "platform.h"
#include "thrdshared.h"


// Shared pipes
static uint8_t qmk_input_buffer[INPUT_BUFFER_SIZE];
PIPE_DECL(qmk_input_pipe, qmk_input_buffer, INPUT_BUFFER_SIZE);
static uint8_t qmk_output_buffer[OUTPUT_BUFFER_SIZE];
PIPE_DECL(qmk_output_pipe, qmk_output_buffer, OUTPUT_BUFFER_SIZE);



#define LCG_A 16807
#define LCG_M 2147483647

#define LCG_Q (LCG_M / LCG_A)
#define LCG_R (LCG_M % LCG_A)

static int32_t lcg_seed = 0;

static MUTEX_DECL(game_mutex);
static THD_WORKING_AREA(game_thread_working_area, 0x800);
static thread_t *game_thread = 0;

static THD_FUNCTION(game_thread_function, arg) {
  start();
}

void lock_game_mutex(void) {
  chMtxLock(&game_mutex);
}

void unlock_game_mutex(void) {
  chMtxUnlock(&game_mutex);
}

bool game_thread_running(void) {
  return game_thread != 0;
}

void qmk_start_game_thread(void) {
  lock_game_mutex();
  if (game_thread == 0) {
    game_thread = chThdCreateStatic(game_thread_working_area,
                                    sizeof(game_thread_working_area),
                                    NORMALPRIO,
                                    game_thread_function,
                                    NULL);
  }
  unlock_game_mutex();
}

void finished(bool success) {
  chMtxLock(&game_mutex);
  game_thread = 0;
  chMtxUnlock(&game_mutex);
  chThdExit(0);
  __builtin_unreachable();
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

int inchar(void) {
  uint8_t ch;
  chPipeReadTimeout(&qmk_input_pipe, &ch, 1, TIME_INFINITE);
  return ch;
}

void outchar(int ch) {
  uint8_t c = (uint8_t) ch;
  chPipeWriteTimeout(&qmk_output_pipe, &c, 1, TIME_INFINITE);
}
