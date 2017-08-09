/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"
#ifdef MOUSEKEY_ENABLE
#  include "mousekey.h"
#endif

extern keymap_config_t keymap_config;

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _MOUSE,
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
    MOUSE,
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

#define RSH_ENT         RSFT_T(KC_ENT)          /* Tap for Enter, hold for Shift (right pinky) */
#define RAISENT         LT(_RAISE, KC_ENT)      /* Tap for Enter, hold for Raise (left thumb)  */
#define GRVMOUS         LT(_MOUSE, KC_GRV)      /* Tap for Grave, hold for Mouse (left pinky)  */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *,-----------------------------------------------------------------------------------------------------------.
 *|   Tab  |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| `/Mouse|    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |    '   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| LShift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   | RSh/Ent|
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Lower |  LCtrl |  LAlt  |  LGUI  |Rais/Ent|      Space      | Raise  |  Menu  |  RAlt  |  RCtrl | Lower  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {GRVMOUS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSH_ENT},
  {LOWER,   KC_LCTL, KC_LALT, KC_LGUI, RAISENT, KC_SPC,  KC_SPC,  RAISE,   KC_APP,  KC_RALT, KC_RCTL, LOWER  }
},

/* Colemak
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |    Q   |    W   |    F   |    P   |    G   |    J   |    L   |    U   |    Y   |    ;   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    A   |    R   |    S   |    T   |    D   |    H   |    N   |    E   |    I   |    O   |   "    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    Z   |    X   |    C   |    V   |    B   |    K   |    M   |    ,   |    .   |    /   |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {_______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______},
  {_______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {_______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Dvorak
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |    "   |    ,   |    .   |    P   |    Y   |    F   |    G   |    C   |    R   |    L   |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    A   |    O   |    E   |    U   |    I   |    D   |    H   |    T   |    N   |    S   |   /    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    ;   |    Q   |    J   |    K   |    X   |    B   |    M   |    W   |    V   |    Z   |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {_______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______},
  {_______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH},
  {_______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Lower
 *,-----------------------------------------------------------------------------------------------------------.
 *|   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |  Vol+  |  Next  |PlyPause|  Mute  |        |        |  Left  |  Down  |   Up   | Right  |  Caps  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |  Vol-  |  Prev  |  Stop  |        |        |        |  Home  |  PgUp  |  PgDn  |  End   |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  {XXXXXXX, KC_VOLU, KC_MNXT, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS},
  {_______, KC_VOLD, KC_MPRV, KC_STOP, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Esc   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |  Del   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |   Ins  |  Home  |  PgUp  |  PrtSc |  SclLk |  Pause |    -   |    =   |    [   |    ]   |   \    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |   Del  |  End   |  PgDn  |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
  {XXXXXXX, KC_INS,  KC_HOME, KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Mouse
 *,-----------------------------------------------------------------------------------------------------------.
 *| Esc    |        |        |        |        |        |        | MS UL  | MS U   | MS UR  | MS WHL | MS WHR |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | MS BT5 | MS BT4 | MS BT3 | MS BT2 |        |        | MS L   |        | MS R   | MS WHU |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        | MS DL  | MS D   | MS DR  | MS WHD |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        | MS BT1 | MS BT1 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = {
  { KC_ESC , BR_TOGG, BR_INC,  BR_DEC,  BR_DEF,  XXXXXXX, XXXXXXX, MMV_UL,  KC_MS_U, MMV_UR,  KC_WH_L, KC_WH_R },
  { _______, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, XXXXXXX, KC_MS_R, KC_WH_U, XXXXXXX },
  { _______, BL_TOGG, BL_INC,  BL_DEC,  XXXXXXX, XXXXXXX, XXXXXXX, MMV_DL,  KC_MS_D, MMV_DR,  KC_WH_D, _______ },
  { XXXXXXX, _______, _______, _______, XXXXXXX, KC_BTN1, KC_BTN1, XXXXXXX, _______, _______, _______, XXXXXXX }
},

/* Plover layer (http://opensteno.org)
 *,-----------------------------------------------------------------------------------------------------------.
 *|    1   |    1   |    1   |    1   |    1   |    1   |    1   |    1   |    1   |    1   |    1   |    1   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |    [   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |    '   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Exit  |        |        |    C   |    V   |                 |    N   |    M   |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Adjust (Lower + Raise)
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |  Reset |        |        |        |        |        |        |        |        |        |   Del  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        | MusMode| Aud on | Aud off| AGnorm | AGswap | Qwerty | Colemak| Dvorak | Plover |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Voice- | Voice+ | Mus on | Musoff | MIDIon | MIDIoff| BL on  | BL off |   BL-  |   BL+  |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL },
  {XXXXXXX, XXXXXXX, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  XXXXXXX},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  BL_ON,   BL_OFF,  BL_DEC,  BL_INC,  _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
float plover_song[][2]     = SONG(PLOVER_SOUND);
float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

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
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
    case MOUSE:
        if (record->event.pressed) {
            layer_off(_RAISE);
            layer_off(_LOWER);
            layer_off(_ADJUST);
            layer_on(_MOUSE);
        } else {
            layer_off(_MOUSE);
        }
        return false;
        break;
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
