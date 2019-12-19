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

enum tapdance_codes {
  TD_MNXT_MPRV = 0
};

// Tapping/holding
#define RSH_ENT         RSFT_T(KC_ENT)          /* Tap for Enter, hold for Shift (right pinky) */

// Layer change
#define LOWER           MO(_LOWER)              /* Momentary use of _LOWER layer */
#define RAISE           MO(_RAISE)              /* Momentary use of _RAISE layer */
#define MMOUSE          MO(_MOUSE)              /* Momentary use of _MOUSE layer */

// Tap dance
#define NXTPRV          TD(TD_MNXT_MPRV)

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
 *|  Ctrl  |  Mouse |  Alt   |   GUI  |  Lower |      Space      |  Raise |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT, \
   KC_LCTL, MMOUSE,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
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
 *|  Ctrl  |  Mouse |  Alt   |   GUI  |  Lower |      Space      |  Raise |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
   KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
   KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT, \
   KC_LCTL, MMOUSE,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
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
 *|  Ctrl  |  Mouse |  Alt   |   GUI  |  Lower |      Space      |  Raise |  Left  |  Down  |   Up   | Right  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_grid( \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
   KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
   KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
   KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RSH_ENT, \
   KC_LCTL, MMOUSE,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Mouse
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |        |        |        |        |        |        |        |        |        |        |  Del   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        | MS UL  | MS U   | MS UR  | MS WHU |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | MS BT5 | MS BT4 | MS BT3 | MS BT2 |        |        | MS L   | MS BT1 | MS R   | MS WHD |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        | MS DL  | MS D   | MS DR  | MS WHL | MS WHR |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        | MS BT1 | MS BT2 |        |  Home  | Pg Up  | Pg Dn  |  End   |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid( \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MMV_UL,  KC_MS_U, MMV_UR,  KC_WH_U, XXXXXXX, \
   _______, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, KC_BTN1, KC_MS_R, KC_WH_D, XXXXXXX, \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MMV_DL,  KC_MS_D, MMV_DR,  KC_WH_L, KC_WH_R, \
   _______, _______, _______, _______, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
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
 *|        |        |        |        |        |                 |        |  Next  |  Vol-  |  Vol+  |  Play  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
   KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
   KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
   KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______, \
   _______, XXXXXXX, _______, _______, _______, _______, _______, _______, NXTPRV,  KC_VOLD, KC_VOLU, KC_MPLY  \
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
 *|        |        |        |        |        |                 |        |  Home  |  PgDn  |  PgUp  |  End   |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
   KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
   KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
   _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______, \
   _______, XXXXXXX, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Plover layer (http://opensteno.org)
 *,-----------------------------------------------------------------------------------------------------------.
 *|    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |    #   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    S   |    T   |    P   |    H   |    *   |    *   |    F   |    P   |    L   |    T   |    D   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    S   |    K   |    W   |    R   |    *   |    *   |    R   |    B   |    G   |    S   |    Z   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Exit  |        |        |    A   |    O   |                 |    E   |    U   |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_preonic_grid( \
   KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    \
   KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    \
   XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, \
   XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
   EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Adjust (Lower + Raise)
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB togg|RGB mode|BL togg |BL step |BR togg | BR inc | BR dec |        | Qwerty |Colemak | Dvorak | Plover |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB hue+|RGB hue-|RGB sat+|RGB sat-|RGB val+|RGB val-|        |        | AU on  | AU off |AG Norm |AG Swap |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB plai|RGB brea|RGB rain|RGB swir|RGB snak|RGB knig|RGB xmas|RGB grad| Mus on |Mus off |Mus Mode|        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Reset |        |        |        |        |                 |        |MIDI on |MIDI off|Mus Voi-|Mus Voi+|
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   RGB_TOG, RGB_MOD, BL_TOGG, BL_STEP, BR_TOGG, BR_INC,  BR_DEC,  XXXXXXX, QWERTY,  COLEMAK, DVORAK,  PLOVER,  \
   RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, \
   RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, MU_ON,   MU_OFF,  MU_MOD,  XXXXXXX, \
   RESET,   XXXXXXX, _______, _______, _______, _______, _______, _______, MI_ON,   MI_OFF,  MUV_DE,  MUV_IN   \
)

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

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

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
#ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(plover_song);
#endif
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
#ifdef AUDIO_ENABLE
        PLAY_SONG(plover_gb_song);
#endif
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
