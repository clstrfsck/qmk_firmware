#include "jd40.h"
#include "config.h"
#include "action_layer.h"

/* Copyright 2015-2017 Jack Humbert
 * Modified 2017 Martin Sandiford
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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  BR_TOGG = SAFE_RANGE,
  BR_INC,
  BR_DEC,
  BR_DEF
};

// Tapping/holding
#define RSH_UP          RSFT_T(KC_UP)           /* Tap for Up, hold for Shift (right pinky) */

// Layer change
#define LOWER           MO(_LOWER)              /* Momentary use of _LOWER layer */
#define RAISE           MO(_RAISE)              /* Momentary use of _RAISE layer */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------.
 * |  Esc  |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   \   |
 * |-----------------------------------------------------------------------------------------------|
 * |  Tab    |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |    Enter    |
 * |-----------------------------------------------------------------------------------------------|
 * |    Shift    |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   | Shft/Up |
 * |-----------------------------------------------------------------------------------------------|
 * | Ctrl  | Meta  | Super |  Raise  |    BkSpc    |    Space    |  Lower  | Left  | Down  | Right |
 * `-----------------------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP_RAW(
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLS,
    KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_ENT,
    KC_LSFT,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, RSH_UP,
    KC_LCTL,KC_LALT,KC_LGUI,RAISE,    KC_BSPC,      KC_SPC,       LOWER,    KC_LEFT,KC_DOWN,KC_RGHT
  ),

/* Lower
 * ,-----------------------------------------------------------------------------------------------.
 * |   ~   |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |   ?   |
 * |-----------------------------------------------------------------------------------------------|
 * |  PrtSc  |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |   _   |   +   |   {   |      }      |
 * |-----------------------------------------------------------------------------------------------|
 * |             |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |       |   :   |   "   |   App   |
 * |-----------------------------------------------------------------------------------------------|
 * |       |       |       |         |             |             |         | Vol-  | Vol+  | Play  |
 * `-----------------------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP_RAW(
    KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_QUES,
    KC_PSCR,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,
    _______,      KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX,KC_COLN,KC_DQUO,KC_APP,
    _______,_______,_______,_______,  _______,      _______,      _______,  KC_VOLD,KC_VOLU,KC_MPLY
  ),

/* Raise
 * ,-----------------------------------------------------------------------------------------------.
 * |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   /   |
 * |-----------------------------------------------------------------------------------------------|
 * |  PrtSc  |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |   -   |   =   |   [   |      ]      |
 * |-----------------------------------------------------------------------------------------------|
 * |             |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |       |   ;   |   '   |  PgUp   |
 * |-----------------------------------------------------------------------------------------------|
 * |       |       |       |         |             |             |         | Home  | PgDn  |  End  |
 * `-----------------------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP_RAW(
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_SLSH,
    KC_PSCR,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,
    _______,      KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX,KC_SCLN,KC_QUOT,KC_PGUP,
    _______,_______,_______,_______,  _______,      _______,      _______,  KC_HOME,KC_PGDN,KC_END
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------------------.
 * |AG Norm|AG Swap|BLtogg |BLstep |BRtogg | BRinc | BRdec |       |       |       |  Ins  |  Del  |
 * |-----------------------------------------------------------------------------------------------|
 * | CapsLck |       |ScrlLck|       |       |       |       |       |       |       |             |
 * |-----------------------------------------------------------------------------------------------|
 * |             |       |       |       |       |       |       |       |       |       |         |
 * |-----------------------------------------------------------------------------------------------|
 * |       |       |       |         |             |             |         |       |       | Reset |
 * `-----------------------------------------------------------------------------------------------'
 */
[_ADJUST] = KEYMAP_RAW(
    AG_NORM,AG_SWAP,BL_TOGG,BL_STEP,BR_TOGG,BR_INC, BR_DEC, XXXXXXX,XXXXXXX,XXXXXXX,KC_INS, KC_DEL,
    KC_CAPS,  XXXXXXX,KC_SLCK,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    _______,      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    _______,_______,_______,_______,  _______,      _______,      _______,  XXXXXXX,XXXXXXX,RESET
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
#if defined(BACKLIGHT_ENABLE) && defined(BACKLIGHT_BREATHING)
    case BR_TOGG:
        if (record->event.pressed) {
            breathing_toggle();
        }
        return false;
        break;
    case BR_INC:
        if (record->event.pressed) {
            breathing_period_inc();
        }
        return false;
        break;
    case BR_DEC:
        if (record->event.pressed) {
            breathing_period_dec();
        }
        return false;
        break;
    case BR_DEF:
        if (record->event.pressed) {
            breathing_period_default();
        }
        return false;
        break;
#endif
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
