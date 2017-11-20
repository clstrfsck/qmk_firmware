#include "jd40.h"
#include "action_layer.h"

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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  BR_TOGG = SAFE_RANGE,
  BR_INC,
  BR_DEC,
  BR_DEF
};

// Tapping/holding
#define RSH_UP          RSFT_T(KC_UP)           /* Tap for Up, hold for Shift (right pinky) */

// Layer change
#define LOWER           MO(_LOWER)              /* Tap for Enter, hold for Lower (left thumb)  */
#define RAISE           MO(_RAISE)              /* Tab for Esc, hold for Raise (right thumb)   */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------.
 * |  Esc  |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Bksp  |
 * |-----------------------------------------------------------------------------------------------|
 * |  Tab    |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |    Enter    |
 * |-----------------------------------------------------------------------------------------------|
 * |    Shift    |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   | Shft/Up |
 * |-----------------------------------------------------------------------------------------------|
 * | Ctrl  | Meta  | Super |  Raise  |    Space    |    Space    |  Lower  | Left  | Down  | Right |
 * `-----------------------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP_RAW(
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_ENT,
    KC_LSFT,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, RSH_ENT,
    KC_LCTL,KC_LALT,KC_LGUI,RAISE,  KC_SPC,         KC_SPC,       LOWER,    KC_LEFT,KC_DOWN,KC_RGHT
    )
},

/* Lower
 * ,-----------------------------------------------------------------------------------------------.
 * |   ~   |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   | Bksp  |
 * |-----------------------------------------------------------------------------------------------|
 * |   Del   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |   _   |   -   |   {   |      }      |
 * |-----------------------------------------------------------------------------------------------|
 * |     Ins     |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  | PrtSc | SLock | Pause |   App   |
 * |-----------------------------------------------------------------------------------------------|
 * |       |       |       |         |             |             |         | Vol-  | Vol+  | Play  |
 * `-----------------------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE },
  {KC_INS,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______ },
  {_______, _______, _______, XXXXXXX, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY }
},

/* Raise
 * ,-----------------------------------------------------------------------------------------------.
 * |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   | Bksp  |
 * |-----------------------------------------------------------------------------------------------|
 * |CapsLock |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |   -   |   =   |   [   |      ]      |
 * |-----------------------------------------------------------------------------------------------|
 * |             |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  | PrtSc |ScrlLck| Pause |  PgUp   |
 * |-----------------------------------------------------------------------------------------------|
 * |       |       |       |         |             |             |         | Home  | PgDn  |  End  |
 * `-----------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  {KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS },
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  _______ },
  {_______, _______, _______, XXXXXXX, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END  }
},

/* Adjust (Lower + Raise)
 *,-----------------------------------------------------------------------------------------------------------.
 *|RGB togg|RGB mode|BL togg |BL step |BR togg | BR inc | BR dec |        | Qwerty |Colemak | Dvorak | Plover |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB hue+|RGB hue-|RGB sat+|RGB sat-|RGB val+|RGB val-|        |        | AU on  | AU off |AG Norm |AG Swap |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|RGB plai|RGB brea|RGB rain|RGB swir|RGB snak|RGB knig|RGB xmas|RGB grad| Mus on |Mus off |Mus Mode|        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|  Reset |        |        |        |        |                 |        |MIDI on |MIDI off|Mus Voi-|Mus Voi+|
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {RGB_TOG, RGB_MOD, BL_TOGG, BL_STEP, BR_TOGG, BR_INC,  BR_DEC,  XXXXXXX, QWERTY,  COLEMAK, DVORAK,  PLOVER  },
  {RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP },
  {RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, MU_ON,   MU_OFF,  MU_MOD,  XXXXXXX },
  {RESET,   _______, _______, XXXXXXX, _______, _______, _______, _______, MI_ON,   MI_OFF,  MUV_DE,  MUV_IN  }
}

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

// 
// Local Variables:
// mode: c
// coding: utf-8
// indent-tabs-mode: nil
// c-basic-offset: 2
// End:
