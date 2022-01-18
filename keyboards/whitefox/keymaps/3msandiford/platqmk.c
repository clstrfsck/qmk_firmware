#include <stdint.h>

#include "quantum.h"

#include "ch.h"
#include "platqmk.h"
#include "platform.h"


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

void start_game(void) {
  chMtxLock(&game_mutex);
  if (game_thread == 0) {
    game_thread = chThdCreateStatic(game_thread_working_area,
                                    sizeof(game_thread_working_area),
                                    NORMALPRIO,
                                    game_thread_function,
                                    NULL);
  }
  chMtxUnlock(&game_mutex);
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

#define GAME_INPUT_DATA_SIZE 32
static MUTEX_DECL(game_input_mutex);
static CONDVAR_DECL(game_input_available_cond);
static volatile bool game_ready_for_input = false;
static volatile bool game_input_available = false;
static char game_input_data[GAME_INPUT_DATA_SIZE + 1];
static uint16_t game_input_index = 0;

int inchar(void) {
  chMtxLock(&game_input_mutex);
  game_ready_for_input = true;
  while (!game_input_available) {
    chCondWait(&game_input_available_cond);
  }
  game_ready_for_input = false;
  char input = game_input_data[game_input_index++];
  if (input == 0) {
    game_input_index = 0;
    game_input_available = false;
    input = '\n';
  }
  chMtxUnlock(&game_input_mutex);
  return input;
}

void outchar(int ch) {
  send_char(ch);
}


static bool process_input(void) {
  bool result = true;
  chMtxLock(&game_input_mutex);
  if (!game_ready_for_input) {
    result = false;
  } else {
    game_input_data[game_input_index] = '\0';
    game_input_index = 0;
    game_input_available = true;
    chCondSignal(&game_input_available_cond);
  }
  chMtxUnlock(&game_input_mutex);
  return result;
}

static bool remove_input(void) {
  bool result = true;
  chMtxLock(&game_input_mutex);
  if (!game_ready_for_input || game_input_index == 0) {
    result = false;
  } else {
    game_input_index -= 1;
  }
  chMtxUnlock(&game_input_mutex);
  return result;
}

static bool add_input(char ch) {
  bool result = true;
  chMtxLock(&game_input_mutex);
  if (!game_ready_for_input || game_input_index >= GAME_INPUT_DATA_SIZE) {
    result = false;
  } else {
    game_input_data[game_input_index++] = ch;
  }
  chMtxUnlock(&game_input_mutex);
  return result;
}


const char keycode_to_ascii_lut[58] = {
  0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'
};

const char shifted_keycode_to_ascii_lut[58] = {
  0, 0, 0, 0, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 0, 0, 0, '\t', ' ', '_', '+', '{', '}', '|', 0, ':', '\'', '~', '<', '>', '?'
};

bool process_game_key(uint16_t keycode, keyrecord_t *record) {
  bool result = true;
  chMtxLock(&game_mutex);
  if (game_thread) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
      keycode = keycode & 0xFF;
    }
    if (!game_ready_for_input) {
      result = false;
    } else if (record->event.pressed && keycode < 256) {
      switch (keycode) {
      case KC_ENTER:
        result = process_input();
        break;
      case KC_BACKSPACE:
        result = remove_input();
        break;
      default:
        if (keycode <= 58) {
          char char_to_add = 0;
          if (get_mods() & (MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_RIGHT_SHIFT))) {
            char_to_add = shifted_keycode_to_ascii_lut[keycode];
          } else if (get_mods() == 0) {
            char_to_add = keycode_to_ascii_lut[keycode];
          }
          if (char_to_add) {
            result = add_input(char_to_add);
          }
        }
        break;
      }
    }
  }
  chMtxUnlock(&game_mutex);
  return result;
}
