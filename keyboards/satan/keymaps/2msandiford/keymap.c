/* Copyright 2018 Martin Sandiford
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
#include "satan.h"
#include "mousekey.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum gh60_layers {
  _QWERTY,
  _OTHER1,
  _OTHER2
};

enum planck_keycodes {
  AG_TOGG = SAFE_RANGE,
  MMV_UL,
  MMV_UR,
  MMV_DL,
  MMV_DR,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Layer change
#define OTHER1          MO(_OTHER1)              /* Momentary use of _OTHER1 layer */
#define OTHER2          MO(_OTHER2)              /* Momentary use of _OTHER2 layer */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* _QWERTY: Qwerty Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |  ESC  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |    Backsp     |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |    Tab    |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   |     \     |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |  Caps Lock  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Return     |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |       Shift     |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |        Shift        |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |  Ctrl   |   Gui   |   Alt   |                      Space                      |   Alt   |   Fn    |   App   |  Ctrl   |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = {
    { KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC },
    { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS },
    { OTHER2,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, KC_ENT  },
    { KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, KC_RSFT },
    { KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, OTHER1,  KC_APP,  KC_RCTL }
  },

  /* _OTHER1: Function Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |   `   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |      Del      |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * | AG Toggle | PgUp  |   Up  | PgDn  | Home  |  Ins  |BL Togg| MS UL | MS Up | MS UR |       | PrtSc | ScLck |   Pause   |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |             | Left  | Down  | Right |  End  |  Del  |BL  Inc| MS Lf | MS B1 | MS Rt |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |                 |Ply/Pse| Mute  | Next  | Vol-  | Vol+  |BL  Dec| MS DL | MS Dn | MS DR |       |                     |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |         |         |         |                     MS Btn 2                    |         |         |         |         |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
  [_OTHER1] = {
    { KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL  },
    { AG_TOGG, KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_INS,  BL_TOGG, MMV_UL,  KC_MS_U, MMV_UR,  XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS },
    { KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_DEL,  BL_INC,  KC_MS_L, KC_BTN1, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, _______ },
    { _______, XXXXXXX, KC_MPLY, KC_MUTE, KC_MNXT, KC_VOLD, KC_VOLU, BL_DEC,  MMV_DL,  KC_MS_D, MMV_DR,  XXXXXXX, XXXXXXX, _______ },
    { _______, _______, _______, _______, _______, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______ }
  },

  /* _OTHER2: Function Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |   `   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |      Del      |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * | AG Toggle |       |       |       |       |  Ins  |BL Togg| Pg Up |   Up  | Pg Dn | Home  | PrtSc | ScLck |   Pause   |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |             |       |       |       |       |  Del  |BL  Inc| Left  | Down  | Right |  End  |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |                 |Ply/Pse| Mute  | Next  | Vol-  | Vol+  |BL  Dec|       |       |       |       |                     |
   * |-----------------------------------------------------------------------------------------------------------------------|
   * |         |         |         |                     MS Btn 2                    |         |  Caps   |         |         |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
  [_OTHER2] = {
    { KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL  },
    { AG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  BL_TOGG, KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_PSCR, KC_SLCK, KC_PAUS },
    { OTHER2,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  BL_INC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, XXXXXXX, _______ },
    { _______, XXXXXXX, KC_MPLY, KC_MUTE, KC_MNXT, KC_VOLD, KC_VOLU, BL_DEC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______ },
    { _______, _______, _______, _______, _______, KC_BTN2, _______, _______, _______, _______, _______, KC_CAPS, _______, _______ }
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case AG_TOGG:
    if (record->event.pressed) {
      if (!eeconfig_is_enabled()) {
        eeconfig_init();
      }
      keymap_config.raw = eeconfig_read_keymap();
      // Keep them in sync
      keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
      keymap_config.swap_ralt_rgui = keymap_config.swap_lalt_lgui;
      eeconfig_update_keymap(keymap_config.raw);
      clear_keyboard(); // clear to prevent stuck keys
    }
    return false;
    break;
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
