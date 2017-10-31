#include "tada68.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum tada68_layers
{
  _BL,
  _FL
};

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _BL: (Base Layer) Default Layer
 *,-------------------------------------------------------------------------------------------------------------------------------.
 *|  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |   Backspace   |   `   |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|     Tab   |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   |     \     |  Del  |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|  Caps Lock  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Return     |  PgUp |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|      Shift      |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |    Shift    |   Up  |  PgDn |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|   Ctrl  |   Win   |   Alt   |                       Space                     |  Alt  |   FN  |  Ctrl |  Left |  Down | Right |
 *`-------------------------------------------------------------------------------------------------------------------------------'
 */
[_BL] = LAYOUT_ansi(
   KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,        KC_GRV,  \
   KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL,  \
   KC_CAPS,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,           KC_PGUP, \
   KC_LSFT,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,      KC_UP,  KC_PGDN, \
   KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,                                           KC_RALT,MO(_FL),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

/* Keymap _FL: Function Layer
 *,-------------------------------------------------------------------------------------------------------------------------------.
 *|       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |               |  Ins  |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|           |MS Btn1| MS Up |MS Btn2|MS Btn3|       |AG Norm|AG Swap|       |       | PScrn | SLock | Pause |           |       |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|             |MS Left|MS Down|MS Rght|       |       |  BL-  | BLTog |  BL+  |       |       |       |                 |       |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|                 |  Undo |  Cut  |  Copy | Paste |       |       | Vol-  | Vol+  | Mute  | Skip  | Play/Pause  | PgUp  |  App  |
 *|-------------------------------------------------------------------------------------------------------------------------------|
 *|         |         |         |                                                 |       |       |       | Home  | PgDn  |  End  |
 *`-------------------------------------------------------------------------------------------------------------------------------'
 */
[_FL] = LAYOUT_ansi(
   _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,        KC_INS,  \
   _______,    KC_BTN1,KC_MS_U,KC_BTN2,KC_BTN3,_______,AG_NORM,AG_SWAP,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______,    _______, \
   _______,      KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,BL_DEC, BL_TOGG,BL_INC, _______,_______,_______,_______,          _______, \
   _______,          KC_UNDO,KC_CUT, KC_COPY,KC_PSTE,_______,_______,KC_MUTE,KC_VOLD,KC_VOLU,KC_MNXT,KC_MPLY,      KC_PGUP,KC_APP,  \
   _______,  _______,  _______,  _______,                                          _______,_______,_______,KC_HOME,KC_PGDN,KC_END ),
};

// 
// Local Variables:
// mode: c
// coding: utf-8
// indent-tabs-mode: nil
// c-basic-offset: 2
// End:
