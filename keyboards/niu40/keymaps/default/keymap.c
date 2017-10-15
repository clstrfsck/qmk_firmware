/* Copyright 2017 Martin Sandiford
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

enum niu40_layers {
  _LAYER0,
  _LAYER1,
  _LAYER2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer0
 *,-----------------------------------------------------------------------------------------------------------.
 *|  Esc   |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Tab   |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |  Enter |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |   Up   |    '   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Ctrl  |   GUI  |  Caps  |   Alt  |  MO(1) |      Space      |  MO(2) |    /   |  Left  |  Down  |  Right |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LAYER0] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT  },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_QUOT },
  {KC_LCTL, KC_LGUI, KC_CAPS, KC_LALT, MO(1),   KC_SPC,  KC_SPC,  MO(2),   KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT }
},

/* Layer1
 *,-----------------------------------------------------------------------------------------------------------.
 *|    `   |   F1   |   F2   |   F3   |   F4   |   F5   |RGB Mode|RGB Togg|   P7   |   P8   |   P9   |   P+   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |  Vol+  |  Vol-  |  Mute  |RGB hue+|RGB hue-|RGB sat+|RGB sat-|   P4   |   P5   |   P6   |   P-   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        | BL Togg| BL Step|        |RGB val+|RGB val-|   P1   |   P2   |   P3   |   P*   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Reset |        |        |        |        |                 |        | PEnter |   P0   |   P.   |   P/   |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LAYER1] = {
  {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RGB_MOD, RGB_TOG, KC_P7,   KC_P8,   KC_P9,   KC_PPLS },
  {_______, KC_VOLU, KC_VOLD, KC_MUTE, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_P4,   KC_P5,   KC_P6,   KC_PMNS },
  {_______, _______, _______, BL_TOGG, BL_STEP, _______, RGB_VAI, RGB_VAD, KC_P1,   KC_P2,   KC_P3,   KC_PAST },
  {RESET,   _______, _______, _______, _______, _______, _______, _______, KC_PENT, KC_P0,   KC_PDOT, KC_PSLS }
},

/* Layer2
 *,-----------------------------------------------------------------------------------------------------------.
 *|    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |    -   |    =   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |   Ins  |  Home  |  PgUp  |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |   Del  |   End  |  PgDn  |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |                 |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LAYER2] = {
  {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL  },
  {_______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
}

};

// 
// Local Variables:
// mode: c
// coding: utf-8
// indent-tabs-mode: nil
// c-basic-offset: 2
// End:
