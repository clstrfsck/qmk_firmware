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
#include "xd75.h"
#include "mousekey.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _MOUSE,
  _FUNC
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BR_TOGG,
  BR_INC,
  BR_DEC,
  BR_DEF,
  MMV_UL,
  MMV_UR,
  MMV_DL,
  MMV_DR
};

// Layer change
#define MFUNC           MO(_FUNC)               /* Momentary function layer */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *,--------------------------------------------------------------------------------------------------------------------------------------.
 *|   Esc  |    `   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |    -   |    =   |  BkSpc |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|   Tab  |   Tab  |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |    [   |    ]   |    \   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Caps  |  Caps  |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |   '    |  Enter |  Enter |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   |  Shift |   Up   |  PrtSc |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|   App  |   FN   |  Ctrl  |   Alt  |   GUI  |               Space               |   GUI  |   Alt  |  Ctrl  |  Left  |  Down  |  Right |
 *`--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC },
  {KC_TAB,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS },
  {KC_CAPS, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT  },
  {KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PSCR },
  {KC_APP,  MFUNC,   KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT }
},

/* Mouse
 *,--------------------------------------------------------------------------------------------------------------------------------------.
 *|AG  norm|AG  swap|    F1  |    F2  |    F3  |    F4  |    F5  |    F6  |    F7  |    F8  |    F9  |   F10  |   F11  |   F12  |   Del  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB togg|RGB mode|BL togg |BL step |BR togg | BR inc | BR dec |        | MS UL  | MS U   | MS UR  | MS WHU |  PrtSc |  ScrLk |  Pause |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB hue+|RGB hue-|RGB sat+|RGB sat-|RGB val+|RGB val-|        |        | MS L   | MS BT1 | MS R   | MS WHD | MS BT2 | MS BT3 |   Ins  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB plai|RGB brea|RGB rain|RGB swir|RGB snak|RGB knig|RGB xmas|RGB grad| MS DL  | MS D   | MS DR  |        |        |  PgUp  |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                                   |  Reset |        |        |  Home  |  PgUp  |   End  |
 *`--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_FUNC] = {
  {AG_NORM, AG_SWAP, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL  },
  {RGB_TOG, RGB_MOD, BL_TOGG, BL_STEP, BR_TOGG, BR_INC,  BR_DEC,  _______, MMV_UL,  KC_MS_U, MMV_UR,  KC_WH_U, KC_PSCR, KC_SLCK, KC_PAUS },
  {RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, KC_MS_L, KC_BTN1, KC_MS_R, KC_WH_D, KC_BTN2, KC_BTN3, KC_INS  },
  {RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, MMV_DL,  KC_MS_D, MMV_DR,  _______, _______, KC_PGUP, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   _______, _______, KC_HOME, KC_PGDN, KC_END  }
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    PORTB &= ~(1 << 2);
  } else {
    PORTB |= (1 << 2);
  }

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    // TODO
  } else {
    // TODO
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    // TODO
  } else {
    // TODO
  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {
    // TODO
  } else {
    // TODO
  }

  if (usb_led & (1 << USB_LED_KANA)) {
    // TODO
  } else {
    // TODO
  }
}

// 
// Local Variables:
// mode: c
// coding: utf-8
// indent-tabs-mode: nil
// c-basic-offset: 2
// End:
