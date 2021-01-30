/* Copyright (C) 2019 Martin Sandiford
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

#include "config.h"
#include "preonic.h"
#include "mousekey.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _MOUSE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *,-----------------------------------------------------------------------------------------------------------.
 *|    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |    \   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Esc   |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |    '   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Ctrl  |  Mouse |  Alt   |   GUI  |   Lower/Enter   |   Raise/Space   |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT, \
   KC_LCTL, MMOUSE,  KC_LALT, KC_LGUI, LO_ENT,  LO_ENT,  RA_SPC,  RA_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Colemak
 *,-----------------------------------------------------------------------------------------------------------.
 *|    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |    \   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    Q   |    W   |    F   |    P   |    G   |    J   |    L   |    U   |    Y   |    ;   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Esc   |    A   |    R   |    S   |    T   |    D   |    H   |    N   |    E   |    I   |    O   |    '   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    K   |    M   |    ,   |    .   |    /   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Ctrl  |  Mouse |  Alt   |   GUI  |   Lower/Enter   |   Raise/Space   |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
   KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
   KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT, \
   KC_LCTL, MMOUSE,  KC_LALT, KC_LGUI, LO_ENT,  LO_ENT,  RA_SPC,  RA_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 *,-----------------------------------------------------------------------------------------------------------.
 *|    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |    \   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    "   |    ,   |    .   |    P   |    Y   |    F   |    G   |    C   |    R   |    L   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Esc   |    A   |    O   |    E   |    U   |    I   |    D   |    H   |    T   |    N   |    S   |    /   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    ;   |    Q   |    J   |    K   |    X   |    B   |    M   |    W   |    V   |    Z   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Ctrl  |  Mouse |  Alt   |   GUI  |   Lower/Enter   |   Raise/Space   |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_grid( \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
   KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
   KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
   KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RSH_ENT, \
   KC_LCTL, MMOUSE,  KC_LALT, KC_LGUI, LO_ENT,  LO_ENT,  RA_SPC,  RA_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Mouse
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |        |        |        |        |        |        |        |        |        |        |  Del   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        | MS UL  | MS U   | MS UR  | MS WHU |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | MS BT4 | MS BT3 | MS BT2 | MS BT1 |        |        | MS L   | MS BT1 | MS R   | MS WHD |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        | MS DL  | MS D   | MS DR  | MS WHL | MS WHR |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |   Lower/Enter   |   Raise/Space   |  Home  | Pg Up  | Pg Dn  |  End   |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid( \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MMV_UL,  KC_MS_U, MMV_UR,  KC_WH_U, XXXXXXX, \
   _______, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, XXXXXXX, XXXXXXX, KC_MS_L, KC_BTN1, KC_MS_R, KC_WH_D, XXXXXXX, \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MMV_DL,  KC_MS_D, MMV_DR,  KC_WH_L, KC_WH_R, \
   _______, _______, _______, _______, LO_ENT,  LO_ENT,  RA_SPC,  RA_SPC,  KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Lower
 *,-----------------------------------------------------------------------------------------------------------.
 *|   F11  |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |   F10  |   F12  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|    ~   |    !   |    @   |    #   |    $   |    %   |    ^   |    &   |    *   |    (   |    )   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Del   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |    _   |    +   |    {   |    }   |    |   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Ins   |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |  PrtSc |ScrlLock|  Pause |   App  |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |   Lower/Enter   |   Raise/Space   |        |  Prev  |  Next  |  Play  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
   KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
   KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
   KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______, \
   _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY  \
),

/* Raise
 *,-----------------------------------------------------------------------------------------------------------.
 *|   F11  |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |   F10  |   F12  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|CapsLock|   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |    -   |    =   |    [   |    ]   |   \    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |  PrtSc |ScrlLock|  Pause |   App  |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |   Lower/Enter   |   Raise/Space   |  Home  |  PgDn  |  PgUp  |  End   |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
   KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
   KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
   _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______, \
   _______, XXXXXXX, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Adjust (Lower + Raise)
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        | Qwerty |Colemak | Dvorak | Plover |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        | AU on  | AU off |AG Norm |AG Swap |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        | Mus on |Mus off |Mus Mode|        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Reset |        |        |        |   Lower/Enter   |   Raise/Space   |MIDI on |MIDI off|Mus Voi-|Mus Voi+|
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,  COLEMAK, DVORAK,  XXXXXXX, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_ON,   MU_OFF,  MU_MOD,  XXXXXXX, \
   RESET,   XXXXXXX, _______, _______, _______, _______, _______, _______, MI_ON,   MI_OFF,  MUV_DE,  MUV_IN   \
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
  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
  case COLEMAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_COLEMAK);
    }
    return false;
  case DVORAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_DVORAK);
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

// 
// Local Variables:
// mode: c
// coding: utf-8
// indent-tabs-mode: nil
// c-basic-offset: 2
// End:
