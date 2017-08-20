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
#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
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
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV
};

// Mnemonics that fit better into the keymap - not used any more
#define KC_NUTI         S(KC_NUHS)              /* Non-US Tilde (Shift+Non-US Hash)      */
#define KC_NUPI         S(KC_NUBS)              /* Non-US Pipe  (Shift+Non-US Backslash) */

// Tapping/holding
#define RSH_ENT         RSFT_T(KC_ENT)          /* Tap for Enter, hold for Shift (right pinky) */
#define LOWRENT         LT(_LOWER, KC_ENT)      /* Tap for Enter, hold for Lower (left thumb)  */
#define RAISESC         LT(_RAISE, KC_ESC)      /* Tab for Esc, hold for Raise (right thumb)   */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Tab   |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Esc   |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |   '    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|   BL   |  Ctrl  |  Alt   |  GUI   |Lowr/Ent|      Space      |Rais/Esc|  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWRENT, KC_SPC,  KC_SPC,  RAISESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
},

/* Colemak
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Tab   |    Q   |    W   |    F   |    P   |    G   |    J   |    L   |    U   |    Y   |    ;   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Esc   |    A   |    R   |    S   |    T   |    D   |    H   |    N   |    E   |    I   |    O   |   "    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    K   |    M   |    ,   |    .   |    /   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Brite |  Ctrl  |  Alt   |  GUI   |Lowr/Ent|      Space      |Rais/Esc|  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC },
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWRENT, KC_SPC,  KC_SPC,  RAISESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
},

/* Dvorak
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Tab   |    "   |    ,   |    .   |    P   |    Y   |    F   |    G   |    C   |    R   |    L   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Esc   |    A   |    O   |    E   |    U   |    I   |    D   |    H   |    T   |    N   |    S   |   /    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    ;   |    Q   |    J   |    K   |    X   |    B   |    M   |    W   |    V   |    Z   |Shft/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Brite |  Ctrl  |  Alt   |  GUI   | Lower  |      Space      | Raise  |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC },
  {KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH },
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RSH_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWRENT, KC_SPC,  KC_SPC,  RAISESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
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
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END  }
},

/* Raise
 *,-----------------------------------------------------------------------------------------------------------.
 *|    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|CapsLock|   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |    -   |    =   |    [   |    ]   |   \    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |  PrtSc |ScrlLock|  Pause |   App  |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |  Next  |  Vol-  |  Vol+  |  Play  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  {KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS },
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______ },
  {_______, KC_RCTL, KC_RALT, KC_RGUI, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY }
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
 *|        |  Reset |        |AG norm |AG swap |        |        |        |        |        |        |   Del  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |Mus Mode| Aud on |Aud off |        |        | Qwerty | Colemk | Dvorak | Plover |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Voice- | Voice+ | Mus on |Mus off |MIDI on |MIDI off|        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   _______, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, _______, KC_DEL  },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, _______, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______ },
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
}


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

/*
  Added to allow proper layer handling for LOWER/RAISE/ADJUST,
  even when using LT(...) macros.
*/
uint32_t layer_state_set_kb(uint32_t state) {
  bool lower_on = (state & (1UL << _LOWER)) != 0;
  bool raise_on = (state & (1UL << _RAISE)) != 0;
  if (lower_on && raise_on) {
    return state | (1UL << _ADJUST);
  } else {
    return state & ~(1UL << _ADJUST);
  }
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
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        // No need for right shift now available on Enter key
        // register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        // No need for right shift now available on Enter key
        // unregister_code(KC_RSFT);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
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
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
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
