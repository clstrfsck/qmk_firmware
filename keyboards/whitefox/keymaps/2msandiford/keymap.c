/*
Copyright 2018 Martin Sandiford

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* NOTE : This is compatible to WhiteFox Vera Layout only */

#include "whitefox.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default Layer
 * ,-------------------------------------------------------------------------------------------------------------------------------.
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |   \   |   `   |  Ins  |
 * |-------------------------------------------------------------------------------------------------------------------------------|
 * |    Tab    |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   | Backspace |  Del  |
 * |-------------------------------------------------------------------------------------------------------------------------------|
 * |    Caps     |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |       |  Enter  | PgUp  |
 * |-------------------------------------------------------------------------------------------------------------------------------|
 * |  Shift  |       |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |    Shift    |  Up   | PgDn  |
 * |-------------------------------------------------------------------------------------------------------------------------------|
 * |  Ctrl   |   Alt   |   Cmd   |                      Space                      |   Cmd   |   FN0   |   | Left  | Down  | Right |
 * `-------------------------------------------------------------------------------------------------------------------------------'
 */
[0] = KEYMAP( \
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_INS,  \
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,    KC_DEL,  \
    KC_FN1,       KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,XXXXXXX,KC_ENT,   KC_PGUP, \
    KC_LSFT,  XXXXXXX,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,      KC_UP,  KC_PGDN, \
    KC_LCTL,  KC_LGUI,  KC_LALT,KC_SPC,                                             KC_RALT,KC_FN0 ,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT  \
    ),
[1] = KEYMAP( \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,KC_MUTE, \
    _______,    AG_NORM,AG_SWAP,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______ ,   _______, \
    KC_CAPS,      _______,_______,_______,KC_FN4 ,_______,KC_FN5 ,_______,_______,_______,_______,_______,_______,RESET,    KC_VOLU, \
    _______,  _______,_______,_______,KC_FN3 ,_______,KC_FN2 ,_______,_______,KC_MPRV,KC_MNXT,KC_MPLY,_______,      KC_PGUP,KC_VOLD, \
    _______,  _______,  _______,  _______,                                          _______,_______,_______,KC_HOME,KC_PGDN,KC_END   \
    ),
[2] = KEYMAP( \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,KC_MUTE, \
    _______,    AG_NORM,AG_SWAP,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______ ,   _______, \
    KC_FN1 ,      _______,_______,_______,KC_FN4 ,_______,KC_FN5 ,_______,_______,_______,_______,_______,_______,RESET,    KC_VOLU, \
    _______,  _______,_______,_______,KC_FN3 ,_______,KC_FN2 ,_______,_______,KC_MPRV,KC_MNXT,KC_MPLY,_______,      KC_PGUP,KC_VOLD, \
    _______,  _______,  _______,  _______,                                          _______,KC_CAPS,_______,KC_HOME,KC_PGDN,KC_END   \
    ),
};

const uint16_t fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2),

    [2] = ACTION_USAGE_CONSUMER(0x196), // Internet browser
    [3] = ACTION_USAGE_CONSUMER(0x1A0), // Command line processor
    [4] = ACTION_USAGE_CONSUMER(0x1A6), // Integrated help center
    [5] = ACTION_USAGE_CONSUMER(0x1B4), // File browser
};

/* custom action function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
}
