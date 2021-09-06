/* Copyright 2020 noclew
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
#include "mousekey.h"

#ifdef AUDIO_ENABLE
  float song_coin[][2]  = SONG(COIN_SOUND);
#endif

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _MOUSE,
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE = SAFE_RANGE,
    MMV_UL,
    MMV_UR,
    MMV_DL,
    MMV_DR
};

// Tapping/holding
#define RSH_ENT     RSFT_T(KC_ENT)          // Tap for Enter, hold for Shift (right pinky)
#define LO_ENT      LT(_LOWER, KC_ENT)      // Tap for Enter, hold for LOWER
#define RA_SPC      LT(_RAISE, KC_SPC)      // Tap for Space, hold for RAISE

// Layer change
#define MMOUSE      MO(_MOUSE)              // Momentary use of _MOUSE layer

// Shorter names
#define RGB_FWD RGB_MODE_FORWARD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BASE
 * -------------------------------------------------             -------------------------------------------------
 * |   `   |   1   |   2   |   3   |   4   |   5   |             |   6   |   7   |   8   |   9   |   0   |   \   |
 * -------------------------------------------------             -------------------------------------------------
 * | Tab   |   Q   |   W   |   E   |   R   |   T   |             |   Y   |   U   |   I   |   O   |   P   | Bksp  |
 * -------------------------------------------------  ---------  -------------------------------------------------
 * | Esc   |   A   |   S   |   D   |   F   |   G   |  | Del   |  |   H   |   J   |   K   |   L   |   ;   |   '   |
 * -------------------------------------------------  ---------  -------------------------------------------------
 * | Shift |   Z   |   X   |   C   |   V   |   B   |  | Del   |  |   N   |   M   |   ,   |   .   |   /   | SftEnt|
 * -------------------------------------------------  ---------  -------------------------------------------------
 *         | Ctrl  | Mouse | Alt   | Gui   | LwrEnt|             | RaiSpc| Left  | Down  | Up    | Right |
 *         -----------------------------------------             -----------------------------------------
 */

[_BASE] = LAYOUT(
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                 KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                 KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,      KC_DEL,    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,      KC_DEL,    KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,RSH_ENT,
            KC_LCTL,MMOUSE, KC_LALT,KC_LGUI,LO_ENT,               RA_SPC, KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
),

[_MOUSE] = LAYOUT(
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,              XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_DEL,
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,              XXXXXXX,MMV_UL, KC_MS_U,MMV_UR, KC_WH_U,XXXXXXX,
    _______,KC_BTN4,KC_BTN3,KC_BTN2,KC_BTN1,XXXXXXX,   KC_DEL,    XXXXXXX,KC_MS_L,KC_BTN1,KC_MS_R,KC_WH_D,XXXXXXX,
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_DEL,    XXXXXXX,MMV_DL, KC_MS_D,MMV_DR, KC_WH_L,KC_WH_R,
            _______,_______,_______,_______,LO_ENT,               RA_SPC, KC_HOME,KC_PGDN,KC_PGUP,KC_END
),

[_LOWER] = LAYOUT(
    KC_F11, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F12,
    KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,              KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,
    KC_DEL, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,     KC_DEL,    KC_F6,  KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
    KC_INS, KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,    KC_DEL,    KC_F12, KC_PSCR,KC_SLCK,KC_PAUS,KC_APP, RSH_ENT,
            _______,XXXXXXX,_______,_______,_______,              _______,KC_HOME,KC_PGDN,KC_PGUP,KC_END
),

[_RAISE] = LAYOUT(
    KC_F11, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F12,
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                 KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC,
    KC_CAPS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,     KC_DEL,    KC_F6,  KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,KC_BSLS,
    KC_INS, KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,    KC_DEL,    KC_F12, KC_PSCR,KC_SLCK,KC_PAUS,KC_APP, RSH_ENT,
            _______,XXXXXXX,_______,_______,_______,              _______,KC_HOME,KC_PGDN,KC_PGUP,KC_END
),

[_ADJUST] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,              XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    RGB_TOG,RGB_FWD,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,              XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    VLK_TOG,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_DEL,    XXXXXXX,XXXXXXX,AU_ON,  AU_OFF, AG_NORM,AG_SWAP,
    KC_LSFT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_DEL,    XXXXXXX,XXXXXXX,MU_ON,  MU_OFF, MU_MOD, XXXXXXX,
            RESET,  XXXXXXX,_______,_______,_______,              _______,MI_ON,  MI_OFF, MUV_DE, MUV_IN
)
};

#define LOWER_AND_RAISE ((1UL << _LOWER) | (1UL << _RAISE))

/* Added to allow layer handling for LOWER/RAISE/ADJUST,
 * even when using LT(...) macros.
 */
uint32_t layer_state_set_kb(uint32_t state) {
  if ((state & LOWER_AND_RAISE) == LOWER_AND_RAISE) {
    state |= 1UL << _ADJUST;
  } else {
    state &= ~(1UL << _ADJUST);
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
  case RESET:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(song_coin);
#endif
    }
    return false;
#ifdef MOUSEKEY_ENABLE
  case MMV_UL:
    if (record->event.pressed) {
      mousekey_on(KC_MS_UP);
      mousekey_on(KC_MS_LEFT);
    } else {
      mousekey_off(KC_MS_UP);
      mousekey_off(KC_MS_LEFT);
    }
    return false;
  case MMV_UR:
    if (record->event.pressed) {
      mousekey_on(KC_MS_UP);
      mousekey_on(KC_MS_RIGHT);
    } else {
      mousekey_off(KC_MS_UP);
      mousekey_off(KC_MS_RIGHT);
    }
    return false;
  case MMV_DL:
    if (record->event.pressed) {
      mousekey_on(KC_MS_DOWN);
      mousekey_on(KC_MS_LEFT);
    } else {
      mousekey_off(KC_MS_DOWN);
      mousekey_off(KC_MS_LEFT);
    }
    return false;
  case MMV_DR:
    if (record->event.pressed) {
      mousekey_on(KC_MS_DOWN);
      mousekey_on(KC_MS_RIGHT);
    } else {
      mousekey_off(KC_MS_DOWN);
      mousekey_off(KC_MS_RIGHT);
    }
    return false;
#endif
  }
  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  /* With an if statement we can check which encoder was turned. */
  if (index == 0) { /* First encoder */
    /* And with another if statement we can check the direction. */
    if (clockwise) {
      if (IS_LAYER_ON(_LOWER)){
        tap_code(KC_RIGHT);
      } else if (IS_LAYER_ON(_RAISE)){
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_VOLU);
      }
    } else {
      if (IS_LAYER_ON(_LOWER)){
        tap_code(KC_LEFT);
      } else if (IS_LAYER_ON(_RAISE)){
        tap_code(KC_UP);
      } else {
        tap_code(KC_VOLD);
      }
    }
  } else if (index == 1) { /* Second encoder. Only supported by Elite-C */
    if (clockwise) {
      if (IS_LAYER_ON(_LOWER)){
        tap_code(KC_RIGHT);
      } else if (IS_LAYER_ON(_RAISE)){
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_VOLU);
      }
    } else {
      if (IS_LAYER_ON(_LOWER)){
        tap_code(KC_LEFT);
      } else if (IS_LAYER_ON(_RAISE)){
        tap_code(KC_UP);
      } else {
        tap_code(KC_VOLD);
      }
    }
  }
  return true;
}

// 
// Local Variables:
// mode: c
// coding: utf-8
// indent-tabs-mode: nil
// c-basic-offset: 2
// End:
