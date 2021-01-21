/* Copyright 2019 COSEYFANNITUTTI
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_tkl_iso(
      KC_GESC,          KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,   KC_PSCR,  KC_SLCK, KC_PAUS,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME, KC_PGUP,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_DEL,   KC_END,  KC_PGDN,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_ENT, KC_BSLS,
      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, KC_RGUI, MO(1),    KC_RCTL,            KC_LEFT, KC_DOWN, KC_RIGHT),

  [1] = LAYOUT_tkl_iso(
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                     KC_VOLU,
      KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,            KC_TRNS, KC_VOLD, KC_TRNS),

  [2] = LAYOUT_tkl_iso(
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                     KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS),

  [3] = LAYOUT_tkl_iso(
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                     KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS)
};

#ifdef OLED_DRIVER_ENABLE

#define MODS_SFT_MASK   (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_CTL_MASK   (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))
#define MODS_ALT_MASK   (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK   (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

#include <string.h>

#include "wpm.h"
#include "keycode_config.h"

#define MOD_INDICATOR_WIDTH 7

const uint8_t PROGMEM sft_ind[MOD_INDICATOR_WIDTH * 2] = {
  0,68,74,74,74,50,0,
  126,187,181,181,181,205,126
};

const uint8_t PROGMEM ctl_ind[MOD_INDICATOR_WIDTH * 2] = {
  0,60,66,66,66,36,0,
  126,195,189,189,189,219,126
};

const uint8_t PROGMEM alt_ind[MOD_INDICATOR_WIDTH * 2] = {
  0,124,18,18,18,124,0,
  126,131,237,237,237,131,126
};

const uint8_t PROGMEM gui_ind[MOD_INDICATOR_WIDTH * 2] = {
  0,60,66,66,82,116,0,
  126,195,189,189,173,139,126
};

// Draw an indicator
void draw_indicator(uint16_t index, const uint8_t *bitmap, bool on) {
  if (on) {
    bitmap += MOD_INDICATOR_WIDTH;
  }
  for (uint8_t i = 0; i < MOD_INDICATOR_WIDTH; ++i) {
    uint8_t bits = pgm_read_byte(bitmap++);
    oled_write_raw_byte(bits, index++);
  }
}

// Draws a rectangle without the corner pixels included
void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
  for (uint8_t i = 1; i < width; ++i) {
    oled_write_pixel(x + i, y, true);
    oled_write_pixel(x + i, y + height, true);
  }
  for (uint8_t i = 1; i < height; ++i) {
    oled_write_pixel(x, y + i, true);
    oled_write_pixel(x + width, y + i, true);
  }
}

char *uint8toa_nz(uint8_t val, char *buf) {
  if (val != 0) {
    uint8_t digit = val % 10;
    buf = uint8toa_nz(val / 10, buf);
    *buf++ = '0' + digit;
  }
  return buf;
}

void uint8toa(uint8_t val, char *buf) {
  if (val == 0) {
    *buf++ = '0';
  } else {
    buf = uint8toa_nz(val, buf);
  }
  *buf = '\0';
}

void oled_task_user(void) {
  // Keyboard layer status
  oled_write_P(PSTR("Layer: "), false);

  uint8_t layer = get_highest_layer(layer_state);
  char topline[20 + 1];
  switch (layer) {
  case 0:
    strcpy_P(topline, PSTR("Default"));
    break;
  case 1:
    strcpy_P(topline, PSTR("Misc"));
    break;
  default:
    uint8toa(layer, topline);
    break;
  }
  oled_write(topline, false);
  for (uint8_t i = strlen(topline); i < 10; ++i) {
    oled_write_char(' ', false);
  }
  if (keymap_config.swap_lalt_lgui) {
    oled_write_ln_P(PSTR("Mac"), false);
  } else {
    oled_write_ln_P(PSTR("PC"), false);
  }

  // Keyboard LED status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.caps_lock   ? PSTR("CAP ") : PSTR("    "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  oled_write_P(led_state.num_lock    ? PSTR("NUM ") : PSTR("    "), false);
  oled_write_P(keymap_config.swap_control_capslock ? PSTR("SWP ") : PSTR("    "), false); 

  // Modifier status
  uint8_t mods = get_mods();
  uint16_t index = 128 + 128 - (4 * MOD_INDICATOR_WIDTH);
  draw_indicator(index, sft_ind, (mods & MODS_SFT_MASK) != 0);
  index += MOD_INDICATOR_WIDTH;
  draw_indicator(index, ctl_ind, (mods & MODS_CTL_MASK) != 0);
  index += MOD_INDICATOR_WIDTH;
  draw_indicator(index, alt_ind, (mods & MODS_ALT_MASK) != 0);
  index += MOD_INDICATOR_WIDTH;
  draw_indicator(index, gui_ind, (mods & MODS_GUI_MASK) != 0);

  // WPM
  oled_set_cursor(7, 3);
  oled_write_P(PSTR("WPM: "), false);
  char wpm[3 + 1];
  uint8toa(get_current_wpm(), wpm);
  oled_write(wpm, false);
  oled_write_char(' ', false);

  // Matrix display
#define MATRIX_DISPLAY_X 0
#define MATRIX_DISPLAY_Y (31 - (MATRIX_ROWS + 3))
  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    matrix_row_t row = matrix_get_row(x);
    for (uint8_t y = 0; y < MATRIX_COLS; y++) {
      bool on = (row & (1UL << y)) != 0;
      oled_write_pixel(MATRIX_DISPLAY_X + y + 2, MATRIX_DISPLAY_Y + x + 2, on);
    }
  }
  draw_rect(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, MATRIX_COLS + 3, MATRIX_ROWS + 3);
}
#endif
