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

enum f60_layers {
    _DEFAULT,
    _LAYER1
};

enum f60_keycodes {
    MMV_UL = SAFE_RANGE,
    MMV_UR,
    MMV_DL,
    MMV_DR
};

// Print screen on Mac
#define KN_PSCR LSFT(LCMD(KC_4))

// Fillers to make layering more clear
#define _______  KC_TRNS
#define ___T___  KC_TRNS
#define XXXXXXX  KC_NO

// Swap control/caps
#define CC_NORM  MAGIC_UNSWAP_CONTROL_CAPSLOCK
#define CC_SWAP  MAGIC_SWAP_CONTROL_CAPSLOCK

// RShift when held, up otherwise
#define RS_UP    RSFT_T(KC_UP)
// RShift when held, pgup otherwise
#define RS_PGUP  RSFT_T(KC_PGUP)

#define LAYER1   MO(_LAYER1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default Layer
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |  Esc  |       |   F1  |   F2  |   F3  |   F4  |   |   F5  |   F6  |   F7  |   F8  |   |   F9  |  F10  |  F11  |  F12  |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |   \   |   `   |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |    Tab    |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   | Backspace |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |    Caps     |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Enter      |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |      Shift      |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |   Shift/Up  |  Del  |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |  Ctrl   |   Alt   |   Cmd   |                      Space                      |  Cmd  |   F0  | Left  | Down  | Right |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_DEFAULT] = LAYOUT(
    KC_ESC,         KC_F1,  KC_F2,  KC_F3,  KC_F4,      KC_F5,  KC_F6,  KC_F7,  KC_F8,      KC_F9,  KC_F10, KC_F11, KC_F12,
    KN_PSCR,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,
    KC_CAPS,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
    KC_LSFT,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,RS_UP,        KC_DEL,
    KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,                                           KC_RALT,LAYER1, KC_LEFT,KC_DOWN,KC_RGHT
    ),
/* Layer 1: Fn Layer
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * | Reset |       |   F1  |   F2  |   F3  |   F4  |   |   F5  |   F6  |   F7  |   F8  |   | AGNrm | AGSwp | CCNrm | CCSwp |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |  Esc  |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |   \   |  Mute |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |    Tab    | MS UL | MS UP | MS UR | MS WU |   T   |   Y   |   U   |   I   |   O   | PrtSc | ScLck | Pause | Volume Up |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |    Caps     | MS LF | MS B1 | MS RG | MS WD |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |    Volume Dn    |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |      Shift      | MS DL | MS DN | MS DR | MS B2 |   B   |   N   |   M   | MPrev | MNext | MPlay |  Shift/PgUp |  Ins  |
 * |-----------------------------------------------------------------------------------------------------------------------|
 * |  Ctrl   |   Alt   |   Cmd   |                      MS B1                      |  Cmd  |   F0  |  Home |  PgDn |  End  |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_LAYER1] = LAYOUT( \
    RESET,          _______,_______,_______,_______,    _______,_______,_______,_______,    AG_NORM,AG_SWAP,CC_NORM,CC_SWAP,
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_MUTE,
    _______,    MMV_UL, KC_MS_U,MMV_UR, KC_WH_U,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,KC_VOLU,
    _______,      KC_MS_L,KC_BTN1,KC_MS_R,KC_WH_D,_______,_______,_______,_______,_______,_______,_______,KC_VOLD,
    _______,          MMV_DL, KC_MS_D,MMV_DR, KC_BTN2,_______,_______,_______,KC_MPRV,KC_MNXT,KC_MPLY,RS_PGUP,      KC_INS,
    _______,  _______,  _______,  KC_BTN1,                                          _______,_______,KC_HOME,KC_PGDN,KC_END
    ),
};

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
