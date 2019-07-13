/*
Copyright 2019 Martin Sandiford

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

#include QMK_KEYBOARD_H

enum m2_layers {
    _DEFAULT,
    _LAYER0,
    _LAYER1
};

enum m2_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

// Swap control/caps
#define CC_NORM MAGIC_UNSWAP_CONTROL_CAPSLOCK
#define CC_SWAP MAGIC_SWAP_CONTROL_CAPSLOCK

#define RGB_MFW RGB_MODE_FORWARD
#define RGB_MRV RGB_MODE_REVERSE

// RShift when held, up otherwise
#define RS_UP    RSFT_T(KC_UP)
// RShift when held, pgup otherwise
#define RS_PGUP  RSFT_T(KC_PGUP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default Layer
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |   \   |   `   |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |    Tab    |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   | Backspace |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |    Caps     |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |       |  Enter  |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |  Shift  |       |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |    Shift    |  F1   |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |  Ctrl   |   Alt   |   Cmd   |       |              Space              |       |  Cmd  |   F0  | Left  | Down  | Right |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_DEFAULT] = LAYOUT(
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,   \
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,      \
    KC_CAPS,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,XXXXXXX,KC_ENT,     \
    KC_LSFT,  XXXXXXX,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,XXXXXXX,RS_UP,LAYER1,   \
    KC_LCTL,  KC_LGUI,  KC_LALT,  XXXXXXX,KC_SPC,                           XXXXXXX,KC_RALT,LAYER0 ,KC_LEFT,KC_DOWN,KC_RGHT   \
    ),
[_LAYER0] = LAYOUT( \
    RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_MUTE,  \
    _______,    AG_NORM,AG_SWAP,CC_NORM,CC_SWAP,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,KC_DEL,       \
    _______,      BL_TOGG,BL_INC ,BL_DEC ,BL_BRTG,_______,_______,_______,_______,_______,_______,KC_INS, _______,KC_VOLU,    \
    _______,  _______,_______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MNXT,KC_MPLY,_______,RS_PGUP,KC_VOLD,\
    _______,  _______,  _______,  _______,_______,                          _______,_______,_______,KC_HOME,KC_PGDN,KC_END    \
    ),
[_LAYER1] = LAYOUT( \
    RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_MUTE,  \
    _______,    AG_NORM,AG_SWAP,CC_NORM,CC_SWAP,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,KC_DEL,       \
    _______,      RGB_TOG,RGB_MFW,RGB_MRV,RGB_SPI,RGB_SPD,_______,_______,_______,_______,_______,KC_INS, _______,KC_VOLU,    \
    _______,  _______,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,_______,KC_MPRV,KC_MNXT,KC_MPLY,_______,RS_PGUP,_______,\
    _______,  _______,  _______,  _______,_______,                          _______,_______,XXXXXXX,KC_HOME,KC_PGDN,KC_END    \
    ),
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LAYER0:
        if (record->event.pressed) {
            layer_on(_LAYER0);
        } else {
            layer_off(_LAYER0);
        }
        return false;
        break;
    case LAYER1:
        if (record->event.pressed) {
            layer_on(_LAYER1);
        } else {
            layer_off(_LAYER1);
        }
        return false;
        break;
    }
    return true;
}
