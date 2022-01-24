#include "thrdqmk.h"
#include "thrdshared.h"


#define INPUT_DATA_SIZE (INPUT_BUFFER_SIZE - 1)
static uint8_t input_data[INPUT_DATA_SIZE + 1];
static uint16_t input_index = 0;


// FIXME - should disable key processing until game ready for input.
// The re-enabling when input is required is not implemented yet.
// Kind of works anyway as qmk_process_output blocks the QMK thread.
static bool ready_for_input = true;

static const char keycode_to_ascii_lut[58] = {
  0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ',
  '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'
};

static const char shifted_keycode_to_ascii_lut[58] = {
  0, 0, 0, 0, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 0, 0, 0, '\t', ' ',
  '_', '+', '{', '}', '|', 0, ':', '\'', '~', '<', '>', '?'
};

#define LUT_KEYCODES (sizeof(keycode_to_ascii_lut) / sizeof(keycode_to_ascii_lut[0]))

static void process_input(void) {
  input_data[input_index] = '\n';
  chPipeWriteTimeout(&qmk_input_pipe, input_data, input_index + 1, TIME_INFINITE);
  input_index = 0;
  ready_for_input = false;
}

static bool remove_input(void) {
  if (input_index > 0) {
    input_index -= 1;
    return true;
  }
  return false;
}

static bool add_input(char ch) {
  if (input_index < INPUT_DATA_SIZE) {
    input_data[input_index++] = ch;
    return true;
  }
  return false;
}


// FIXME - shift keys not yet supported/working
bool qmk_process_input(uint16_t keycode, keyrecord_t *record) {
  bool result = true;
  lock_game_mutex();
  if (game_thread_running()) {
    result = false;
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
      keycode = keycode & 0xFF;
    }
    if (record->event.pressed && keycode < 256) {
      switch (keycode) {
      case KC_ENTER:
        process_input();
        tap_code(keycode);
        break;
      case KC_BACKSPACE:
        if (remove_input()) {
          tap_code(keycode);
        }
        break;
      default:
        if (keycode < LUT_KEYCODES) {
          char ch = 0;
          if (get_mods() & (MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_RIGHT_SHIFT))) {
            ch = shifted_keycode_to_ascii_lut[keycode];
          } else if (get_mods() == 0) {
            ch = keycode_to_ascii_lut[keycode];
          }
          if (ch && add_input(ch)) {
            send_char(ch);
          }
        }
        break;
      }
    }
  }
  unlock_game_mutex();
  return result;
}

void qmk_process_output(void) {
  uint8_t ch;
  while (0 != chPipeReadTimeout(&qmk_output_pipe, &ch, sizeof(ch), TIME_IMMEDIATE)) {
    if (ch == 0) {
      ready_for_input = true;
    } else {
      send_char(ch);
    }
  }
}

void qmk_start_game(void) {
  qmk_start_game_thread();
}
