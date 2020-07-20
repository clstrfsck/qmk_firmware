/* Copyright 2019 Martin Sandiford
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

enum s50_layers {
  _DEFAULT,
  _MOUSE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum s50_keycodes {
  MMV_UL = SAFE_RANGE,
  MMV_UR,
  MMV_DL,
  MMV_DR
};

enum tapdance_codes {
  TD_MNXT_MPRV = 0
};

// Fillers to make layering more clear
#define _______  KC_TRNS
#define XXXXXXX  KC_NO

// Swap control/caps
#define CC_NORM  MAGIC_UNSWAP_CONTROL_CAPSLOCK
#define CC_SWAP  MAGIC_SWAP_CONTROL_CAPSLOCK

// Layer change
#define LOWER           MO(_LOWER)              /* Momentary use of _LOWER layer */
#define RAISE           MO(_RAISE)              /* Momentary use of _RAISE layer */
#define MMOUSE          MO(_MOUSE)              /* Momentary use of _MOUSE layer */

// Tap dance
#define NXTPRV          TD(TD_MNXT_MPRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default Layer
 * ,-------------------------------------------------------------------------------------------------------.
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   \   |   `   |
 * |-------------------------------------------------------------------------------------------------------|
 * |    Tab    |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |           |
 * |---------------------------------------------------------------------------------------------.  Enter  |
 * |    Ctrl     |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |         |
 * |-------------------------------------------------------------------------------------------------------|
 * | Shift | Bksp  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   | Shift |
 * |-------------------------------------------------------------------------------------------------------|
 * | Caps  | Mouse |  Alt  |  GUI  | Lower |         Space         | Raise | Left  | Down  |  Up   | Right |
 * `-------------------------------------------------------------------------------------------------------'
 */
[_DEFAULT] = LAYOUT( \
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS,KC_GRV,  \
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,                \
    KC_LCTL,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,    \
    KC_LSFT,KC_QUOT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT, \
    KC_CAPS,MMOUSE, KC_LALT,KC_LGUI,LOWER,           KC_SPC,        RAISE,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT  \
  ),
/* Mouse Layer
 * ,-------------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------------------------------------------------------------------------------------------------------|
 * |           |       |       |       |       |       |       | MS UR | MS U  | MS UR | MSWHU |           |
 * |---------------------------------------------------------------------------------------------.         |
 * |             | MSBT5 | MSBT4 | MSBT3 | MSBT2 |       |       | MS L  | MSBT1 | MS R  | MSWHD |         |
 * |-------------------------------------------------------------------------------------------------------|
 * |       |       |       |       |       |       |       |       | MS DL | MS D  | MS DR | MSWHL | MSWHR |
 * |-------------------------------------------------------------------------------------------------------|
 * |       |       |       |       |       |         MSBT1         |       | Home  | Pg Dn | Pg Up |  End  |
 * `-------------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT( \
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______, \
    _______,    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,MMV_UL, KC_MS_U,MMV_UR, KC_WH_U,             \
    _______,      KC_BTN5,KC_BTN4,KC_BTN3,KC_BTN2,XXXXXXX,XXXXXXX,KC_MS_L,KC_BTN1,KC_MS_R,KC_WH_D,XXXXXXX,   \
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,MMV_DL, KC_MS_D,MMV_DR, KC_WH_L,KC_WH_R, \
    _______,_______,_______,_______,XXXXXXX,         KC_BTN1,       XXXXXXX,KC_HOME,KC_PGDN,KC_PGUP,KC_END   \
  ),
/* Lower Layer
 * ,-------------------------------------------------------------------------------------------------------.
 * |       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
 * |-------------------------------------------------------------------------------------------------------|
 * |           |       |       |       |       |       |       |       |       |       |       |           |
 * |---------------------------------------------------------------------------------------------.         |
 * |             |       |       |       |       |       |       |   -   |   =   |   [   |   ]   |         |
 * |-------------------------------------------------------------------------------------------------------|
 * |  Del  |       |       |       |       |       |       |       | PScr  | SLock | Pause |  App  |       |
 * |-------------------------------------------------------------------------------------------------------|
 * |  Ins  |       |       |       |       |                       |       | Next  | Vol-  | Vol+  | MPlay |
 * `-------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,  \
    _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,             \
    _______,      _______,_______,_______,_______,_______,_______,KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,_______,   \
    _______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,KC_APP, _______, \
    _______,XXXXXXX,_______,_______,_______,         KC_BSPC,       _______,NXTPRV, KC_VOLD,KC_VOLU,KC_MPLY  \
  ),
/* Raise Layer
 * ,-------------------------------------------------------------------------------------------------------.
 * |       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
 * |-------------------------------------------------------------------------------------------------------|
 * |           |       |       |       |       |       |       |       |       |       |       |           |
 * |---------------------------------------------------------------------------------------------.         |
 * |             |       |       |       |       |       |       |   _   |   +   |   {   |   }   |         |
 * |-------------------------------------------------------------------------------------------------------|
 * |       |       |       |       |       |       |       |       | PScr  | SLock | Pause |  App  |       |
 * |-------------------------------------------------------------------------------------------------------|
 * |       |       |       |       |       |                       |       | Home  | Pg Dn | Pg Up |  End  |
 * `-------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,  \
    _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,             \
    _______,      _______,_______,_______,_______,_______,_______,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,_______,   \
    _______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,KC_APP, _______, \
    _______,XXXXXXX,_______,_______,_______,         KC_DEL,        _______,KC_HOME,KC_PGDN,KC_PGUP,KC_END   \
  ),
/* Adjust Layer
 * ,-------------------------------------------------------------------------------------------------------.
 * | RESET |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------------------------------------------------------------------------------------------------------|
 * |           |       |       |       |       |       |       |       |       |       |       |           |
 * |---------------------------------------------------------------------------------------------.         |
 * |             |       |       |       |       |       |       | CCNrm | CCSwp | AGNrm | AGSwp |         |
 * |-------------------------------------------------------------------------------------------------------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------------------------------------------------------------------------------------------------------|
 * |       |       |       |       |       |                       |       |       |       |       |       |
 * `-------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
    RESET,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,             \
    XXXXXXX,      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,CC_NORM,CC_SWAP,AG_NORM,AG_SWAP,XXXXXXX,   \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,_______,_______,_______,         _______,       _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX  \
  ),
};

void tapdance_nxtprv(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_MNXT);
  } else if (state->count >= 2) {
    uint8_t count = state->count - 1;
    tap_code(KC_MPRV);
    if (count > 1) {
      for (uint8_t i = 1; i < count; ++i) {
        wait_ms(TAP_CODE_DELAY);
        tap_code(KC_MPRV);
      }
    }
  }
}


// Tapdance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for next, twice for previous
  [TD_MNXT_MPRV] = ACTION_TAP_DANCE_FN(tapdance_nxtprv)
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
        break;
    case MMV_UR:
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_RIGHT);
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_RIGHT);
        }
        return false;
        break;
    case MMV_DL:
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_LEFT);
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_LEFT);
        }
        return false;
        break;
    case MMV_DR:
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_RIGHT);
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_RIGHT);
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
