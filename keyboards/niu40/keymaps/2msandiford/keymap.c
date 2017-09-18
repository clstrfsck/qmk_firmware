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

#include "config.h"
#include "niu40.h"
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
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  EXT_PLV,
  BR_TOGG,
  BR_INC,
  BR_DEC,
  BR_DEF,
  MMV_UL,
  MMV_UR,
  MMV_DL,
  MMV_DR
};

// Tapping/holding
#define RSH_ENT         RSFT_T(KC_ENT)          /* Tap for Enter, hold for Shift (right pinky) */
#define LOWRENT         LT(_LOWER, KC_ENT)      /* Tap for Enter, hold for Lower (left thumb)  */
#define RAISESC         LT(_RAISE, KC_ESC)      /* Tab for Esc, hold for Raise (right thumb)   */

// Layer change
#define MMOUSE          MO(_MOUSE)              /* Momentary mouse layer                       */

// Shorter RGB modes
#define RGB_MO1 RGB_MODE_PLAIN
#define RGB_MO2 RGB_MODE_BREATHE
#define RGB_MO3 RGB_MODE_RAINBOW
#define RGB_MO4 RGB_MODE_SWIRL
#define RGB_MO5 RGB_MODE_SNAKE
#define RGB_MO6 RGB_MODE_KNIGHT
#define RGB_MO7 RGB_MODE_XMAS
#define RGB_MO8 RGB_MODE_GRADIENT


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Esc   |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |   '    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Mouse |  Ctrl  |  Alt   |  GUI   |Lowr/Ent|      Space      |Rais/Esc|  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT },
  {MMOUSE,  KC_LCTL, KC_LALT, KC_LGUI, LOWRENT, KC_SPC,  KC_SPC,  RAISESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
},

/* Colemak
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Esc   |    Q   |    W   |    F   |    P   |    G   |    J   |    L   |    U   |    Y   |    ;   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    A   |    R   |    S   |    T   |    D   |    H   |    N   |    E   |    I   |    O   |   "    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    K   |    M   |    ,   |    .   |    /   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Mouse |  Ctrl  |  Alt   |  GUI   |Lowr/Ent|      Space      |Rais/Esc|  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC },
  {KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT },
  {MMOUSE,  KC_LCTL, KC_LALT, KC_LGUI, LOWRENT, KC_SPC,  KC_SPC,  RAISESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
},

/* Dvorak
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Esc   |    "   |    ,   |    .   |    P   |    Y   |    F   |    G   |    C   |    R   |    L   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    A   |    O   |    E   |    U   |    I   |    D   |    H   |    T   |    N   |    S   |   /    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    ;   |    Q   |    J   |    K   |    X   |    B   |    M   |    W   |    V   |    Z   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Mouse |  Ctrl  |  Alt   |  GUI   | Lower  |      Space      | Raise  |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC },
  {KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH },
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RSH_ENT },
  {MMOUSE,  KC_LCTL, KC_LALT, KC_LGUI, LOWRENT, KC_SPC,  KC_SPC,  RAISESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
},

/* Mouse
 *,-----------------------------------------------------------------------------------------------------------.
 *|        | BR TOG | BR INC | BR DEC | BR DEF |        |        | MS UL  | MS U   | MS UR  | MS WHL | MS WHR |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | MS BT5 | MS BT4 | MS BT3 | MS BT2 |        |        | MS L   |        | MS R   | MS WHU |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | BL TOG | BL_INC | BL_DEC |        |        |        | MS DL  | MS D   | MS DR  | MS WHD |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        | MS BT1 | MS BT1 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = {
  {_______, BR_TOGG, BR_INC,  BR_DEC,  BR_DEF,  XXXXXXX, XXXXXXX, MMV_UL,  KC_MS_U, MMV_UR,  KC_WH_L, KC_WH_R },
  {_______, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, XXXXXXX, KC_MS_R, KC_WH_U, XXXXXXX },
  {_______, BL_TOGG, BL_INC,  BL_DEC,  XXXXXXX, XXXXXXX, XXXXXXX, MMV_DL,  KC_MS_D, MMV_DR,  KC_WH_D, _______ },
  {_______, _______, _______, _______, XXXXXXX, KC_BTN1, KC_BTN1, XXXXXXX, _______, _______, _______, _______ }
},

/* Lower
 *,-----------------------------------------------------------------------------------------------------------.
 *|    ~   |    !   |    @   |    #   |    $   |    %   |    ^   |    &   |    *   |    (   |    )   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Del   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |    _   |    +   |    {   |    }   |   |    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Ins   |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |  PrtSc |ScrlLock|  Pause |   App  |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |  Home  |  PgDn  |  PgUp  |  End   |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE },
  {KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______ },
  {XXXXXXX, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END  }
},

/* Raise
 *,-----------------------------------------------------------------------------------------------------------.
 *|    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|CapsLock|   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |    -   |    =   |    [   |    ]   |   \    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |  PrtSc |ScrlLock|  Pause |   App  |  Mute  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |  Next  |  Vol-  |  Vol+  |  Play  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  {KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS },
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  KC_MUTE },
  {XXXXXXX, KC_RCTL, KC_RALT, KC_RGUI, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY }
},

/* Plover layer (http://opensteno.org)
 *,-----------------------------------------------------------------------------------------------------------.
 *|    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    S   |    T   |    P   |    H   |    *   |    *   |    F   |    P   |    L   |    T   |    D   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    S   |    K   |    W   |    R   |    *   |    *   |    R   |    B   |    G   |    S   |    Z   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Exit  |        |        |    A   |    O   |                 |    E   |    U   |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1    },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC },
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX }
},

/* Adjust (Lower + Raise)
 *,-----------------------------------------------------------------------------------------------------------.
 *|RGB togg|RGB mode|BL togg |BL step |BR togg | BR inc | BR dec |        |AG norm |AG swap | Qwerty |Colemak |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB hue+|RGB hue-|RGB sat+|RGB sat-|RGB val+|RGB val-|        |        |        |        | Dvorak | Plover |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB plai|RGB brea|RGB rain|RGB swir|RGB snak|RGB knig|RGB xmas|RGB grad|        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Reset |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {RGB_TOG, RGB_MOD, BL_TOGG, BL_STEP, BR_TOGG, BR_INC,  BR_DEC,  XXXXXXX, AG_NORM, AG_SWAP, QWERTY,  COLEMAK },
  {RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DVORAK,  PLOVER  },
  {RGB_MO1, RGB_MO2, RGB_MO3, RGB_MO4, RGB_MO5, RGB_MO6, RGB_MO7, RGB_MO8, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
  {RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
}


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
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_off(_MOUSE);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
      }
      return false;
      break;
#if defined(BACKLIGHT_ENABLE) && defined(BACKLIGHT_BREATHING)
    case BR_TOGG:
        if (record->event.pressed) {
            breathing_toggle();
        }
        return false;
        break;
    case BR_INC:
        if (record->event.pressed) {
            breathing_speed_inc(1);
        }
        return false;
        break;
    case BR_DEC:
        if (record->event.pressed) {
            breathing_speed_dec(1);
        }
        return false;
        break;
    case BR_DEF:
        if (record->event.pressed) {
            breathing_defaults();
        }
        return false;
        break;
#endif
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
