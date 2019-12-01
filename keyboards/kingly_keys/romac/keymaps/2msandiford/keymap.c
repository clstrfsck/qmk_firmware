/* Copyright 2018 Jack Humbert
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

#define KN_PSCR LSFT(LCMD(KC_3))
#define KN_CHAR LCTL(LCMD(KC_SPC))

enum planck_keycodes {
  SWE_01 = SAFE_RANGE,
  SWE_02,
  SWE_03,
  SWE_04,
  SWE_05,
  SWE_06,
  SWE_07,
  SWE_08,
  SWE_09
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KN_PSCR, KN_CHAR,         \
        SWE_01,  SWE_02,  SWE_03,          \
        SWE_04,  SWE_05,  SWE_06,          \
        SWE_07,  SWE_08,  SWE_09           \
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SWE_01:
        if (record->event.pressed) {
            SEND_STRING("Hej allihopa");
        }
        break;
    case SWE_02:
        if (record->event.pressed) {
            SEND_STRING("Jag 'lskar kanelbullar!");
        }
        break;
    case SWE_03:
        if (record->event.pressed) {
            SEND_STRING("IKEA");
        }
        break;
    case SWE_04:
        if (record->event.pressed) {
            SEND_STRING("Sk[l!");
        }
        break;
    case SWE_05:
        if (record->event.pressed) {
            SEND_STRING("Jag vill ha en k;ttbulle till");
        }
        break;
    case SWE_06:
        if (record->event.pressed) {
            SEND_STRING("kn'ckebr;d");
        }
        break;
    case SWE_07:
        if (record->event.pressed) {
            SEND_STRING("Kalles Kaviar");
        }
        break;
    case SWE_08:
        if (record->event.pressed) {
            SEND_STRING("Cool bananas!");
        }
        break;
    case SWE_09:
        if (record->event.pressed) {
            SEND_STRING("Kubernetes!");
        }
        break;
    }
    return true;
}
