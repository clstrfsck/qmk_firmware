#include QMK_KEYBOARD_H
#include "process_unicode_common.h"

// Brevity defines
#define FT KC_TRNS

// Layers
enum custom_layers {
    _BASE,
    _TOP,
    _FRONT,
    _FN
};

enum custom_keycodes {
    // daughter board R1
    H_HELP = SAFE_RANGE,
    H_MACRO,
    H_TERM,
    H_QUOTE,
    H_OVRST,
    H_CLRIN,
    H_CLRSC,
    H_HLOUT,
    H_STOUT,
    H_ABORT,
    H_BREAK,
    H_RSUME,
    H_CALL,

    // daughter board R2
    H_LOCAL,
    H_NETWK,
    H_SYSTM,
    H_REFSH,
    H_BUFFR,
    H_SQUAR,
    H_CIRCL,
    H_TANGL,
    H_DIAMD,
    H_REPT,
    H_XMIT,
    H_STAT,
    H_SUSP,

    // daughter board r3
    H_CLOSE,
    H_OPEN,
    SYM_QUE,
    SYM_EXC,
    SYM_AT,
    SYM_GBP,
    SYM_EUR,
    SYM_JPY,
    SYM_BTK,
    SYM_DQO,
    SYM_DQC,
    SYM_PRI,
    SYM_UND,
    SYM_LCH,
    SYM_RCH,
    SYM_BAR,
    SYM_LBR,
    SYM_RBR,
    H_COMPL,

    // main board r1
    H_FIND,
    H_WRITE,
    H_DQPM, // Double quote with ±
    H_COTI, // : and ~
    H_LBLC, // L brace / L angle
    H_RBRC, // R brace / R angle
    H_UNDO2,

    // main board r2
    H_MARK,
    H_UNDO,
    H_PASTE,
    H_CUT,
    H_LPLB, // Left paren / bracket
    H_RPRB, // Right paren / bracket
    H_CLEAR,

    // main board r3
    H_SLECT,
    H_DEBUG,
    H_MODE,
    H_SCBT, // Semi-colon / backtick
    H_LINE,
    H_PAGE,

    // main board r4
    H_TTY,
    H_LOCK, // lock machine?

    // main board r5
    H_EOF,
    H_7BIT,
    H_SMCIR, // Small circle, middle of keyboard

    // "Top" keycodes
    TOP_Q,
    TOP_W,
    TOP_E,
    TOP_R,
    TOP_T,
    TOP_Y,
    TOP_U,
    TOP_I,
    TOP_O,
    TOP_P,
    TOP_A,
    TOP_S,
    TOP_D,
    TOP_F,
    TOP_G,
    TOP_H,
    TOP_J,
    TOP_K,
    TOP_L,
    TOP_Z,
    TOP_X,
    TOP_C,
    TOP_V,
    TOP_B,
    TOP_N,
    TOP_M,

    // "Front" keycodes
    FRT_DQO,
    FRT_COL,
    FRT_1,
    FRT_2,
    FRT_3,
    FRT_4,
    FRT_5,
    FRT_6,
    FRT_7,
    FRT_8,
    FRT_9,
    FRT_0,
    FRT_MIN,
    FRT_EQU,
    FRT_BSL,
    FRT_LBR,
    FRT_RBR,
    FRT_Q,
    FRT_W,
    FRT_E,
    FRT_R,
    FRT_T,
    FRT_Y,
    FRT_U,
    FRT_I,
    FRT_O,
    FRT_P,
    FRT_LPA,
    FRT_RPA,
    FRT_A,
    FRT_S,
    FRT_D,
    FRT_F,
    FRT_G,
    FRT_H,
    FRT_J,
    FRT_K,
    FRT_L,
    FRT_SCO,
    FRT_SQU,
    FRT_Z,
    FRT_X,
    FRT_C,
    FRT_V,
    FRT_B,
    FRT_N,
    FRT_M,
    FRT_COM,
    FRT_DOT,
    FRT_SLA,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BASE: Base Layer(Default)
     * ,-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |     Help      |     Macro     |#|   Terminal    |     Quote     |   OverStrike  |   ClearInput  |  ClearScreen  |  HoldOutput   |   StopOutput  |     Abort     |     Break     |    Resume     |#|     Call      |     RESET     |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     Local     |    Network    |#|    System     |    Refresh    |     Buffer    |     Square    |     Circle    |   Triangle    |    Diamond    |     Repeat    |    Transmit   |    Status     |#|    Suspend    |    CapsLock   |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |  F1   |  F2   | Close | Open  |#|     Esc       |   ?   |   !   |   @   |   £   |   €   |   ¥   |   '   |   “   |   ”   |   '   |   _   |   <   |   >   |   |   |   {   |   }   |   Complete    |#|   ^   |   %   |   #   |   $   |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###################################################################################################################################################################################################################################|
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |  F3   |  F4   | Find  | Write |#|  Compose  |  "/±  |  :/~  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |   \   |  {/‹  |  }/›  |   Undo    |#|   ~   |   /   |   *   |   -   |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |  F5   |  F6   | Mark  | Undo  |#| Paste |    Cut    |    Tab    |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   (   |   )   |  Bspace   |   Clear   | Begin |#|   7   |   8   |   9   |   +   |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |  F7   |  F8   |Select | Debug |#| Function  |   Mode    |    Top    |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |  Return   |   Line    |   Page    |#|   4   |   5   |   6   |   &   |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |  F9   |  F10  |  TT Y | LOCK  |#| Begin |  End  |  Symbol   |   Shift   |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |   Shift   |   Symbol  |  Up   |  End  |#|   1   |   2   |   3   |   =   |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |  F11  |  F12  | Home  |  EOF  |#| Prior | Next  | 7bit  |  Alt  |   Hyper   | Super |   Ctrl    |   Space   |SMLCIRC|    Del    |   Ctrl    | Super |   Hyper   | Meta  | Left  | Down  | Right |#|  Del  |   0   |   .   |  Run  |
     * `-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_h7v3_183(
        H_HELP,         H_MACRO,          H_TERM,         H_QUOTE,        H_OVRST,        H_CLRIN,        H_CLRSC,        H_HLOUT,        H_STOUT,        H_ABORT,        H_BREAK,        H_RSUME,          H_CALL,         KC_NLCK,
        H_LOCAL,        H_NETWK,          H_SYSTM,        H_REFSH,        H_BUFFR,        H_SQUAR,        H_CIRCL,        H_TANGL,        H_DIAMD,        H_REPT,         H_XMIT,         H_STAT,           H_SUSP,         KC_CLCK,
        KC_F1,  KC_F2,  H_CLOSE,H_OPEN,   KC_ESC,         SYM_QUE,SYM_EXC,SYM_AT, SYM_GBP,SYM_EUR,SYM_JPY,SYM_BTK,SYM_DQO,SYM_DQC,SYM_PRI,SYM_UND,SYM_LCH,SYM_RCH,SYM_BAR,SYM_LBR,SYM_RBR,H_COMPL,          KC_CIRC,KC_PERC,KC_HASH,KC_DLR,

        KC_F3,  KC_F4,  H_FIND, H_WRITE,  KC_LEAD,    H_DQPM, H_COTI, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,H_LBLC, H_RBRC, H_UNDO2,      KC_TILD,KC_PSLS,KC_PAST,KC_PMNS,
        KC_F5,  KC_F6,  H_MARK, H_UNDO,   H_PASTE,H_CUT,      KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   H_LPLB, H_RPRB, KC_BSPC,    H_CLEAR,    KC_HOME,  KC_P7,  KC_P8,  KC_P9,  KC_PPLS,
        KC_F7,  KC_F8,  H_SLECT,H_DEBUG,  MO(_FN),    H_MODE,     MO(_TOP),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   H_SCBT, KC_QUOT,KC_ENT,     H_LINE,     H_PAGE,       KC_P4,  KC_P5,  KC_P6,  KC_AMPR,
        KC_F9,  KC_F10, H_TTY,  H_LOCK,   KC_HOME,KC_END, MO(_FRONT), KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,    MO(_FRONT), KC_UP,  KC_END,   KC_P1,  KC_P2,  KC_P3,  KC_PEQL,
        KC_F11, KC_F12, KC_HOME,H_EOF,    KC_MPRV,KC_MNXT,H_7BIT, KC_LALT,KC_HYPR,    KC_LGUI,KC_LCTL,    KC_SPC,     H_SMCIR,KC_DEL,     KC_RCTL,    KC_RGUI,KC_HYPR,    KC_RGUI,KC_LEFT,KC_DOWN,KC_RGHT,  KC_DEL, KC_P0,  KC_PDOT,KC_PENT
    ),

    /* _TOP: Cadet Symbol Layer (Top Legend)
     * ,-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |               |               |#|               |               |               |               |               |               |               |               |               |               |#|               |               |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |               |               |#|               |               |               |               |               |               |               |               |               |               |#|               |               |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|               |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |               |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###################################################################################################################################################################################################################################|
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|           |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |           |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |           |           |   ∧   |   ∨   |   ⋂   |   ⋃   |   ⊂   |   ⊃   |   ∀   |   ∞   |   ∃   |   ∂   |       |       |           |           |       |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|           |           |           |   ⊥   |   ⊤   |   ⊢   |   ⊣   |   ↑   |   ↓   |   ←   |   →   |   ↔   |   ;   |   '   |           |           |           |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |       |           |           |   ⌊   |   ⌈   |   ≠   |   ≃   |   ≡   |   ≤   |   ≥   |       |       |       |           |           |       |       |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |       |       |       |           |       |           |           |       |           |           |       |           |       |       |       |       |#|       |       |       |       |
     * `-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_TOP] = LAYOUT_h7v3_183(
        FT,             FT,               FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,               FT,             FT,
        FT,             FT,               FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,               FT,             FT,
        FT,     FT,     FT,     FT,       FT,             FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,               FT,     FT,     FT,     FT,

        FT,     FT,     FT,     FT,       FT,         FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,           FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,         FT,         TOP_Q,  TOP_W,  TOP_E,  TOP_R,  TOP_T,  TOP_Y,  TOP_U,  TOP_I,  TOP_O,  TOP_P,  FT,     FT,     FT,         FT,         FT,       FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,         FT,         FT,         TOP_A,  TOP_S,  TOP_D,  TOP_F,  TOP_G,  TOP_H,  TOP_J,  TOP_K,  TOP_L,  FT,     FT,     FT,         FT,         FT,           FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,     FT,         FT,         TOP_Z,  TOP_X,  TOP_C,  TOP_V,  TOP_B,  TOP_N,  TOP_M,  FT,     FT,     FT,     FT,         FT,         FT,     FT,       FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,     FT,     FT,     FT,         FT,     FT,         FT,         FT,     FT,         FT,         FT,     FT,         FT,     FT,     FT,     FT,       FT,     FT,     FT,     FT
    ),

    /* _FRONT: Cadet Symbol Layer (Front Legend)
     * ,-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |               |               |#|               |               |               |               |               |               |               |               |               |               |#|               |               |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |               |               |#|               |               |               |               |               |               |               |               |               |               |#|               |               |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|               |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |               |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###################################################################################################################################################################################################################################|
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|           |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |           |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |           |           |   ∧   |   ∨   |   ⋂   |   ⋃   |   ⊂   |   ⊃   |   ∀   |   ∞   |   ∃   |   ∂   |       |       |           |           |       |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|           |           |           |   ⊥   |   ⊤   |   ⊢   |   ⊣   |   ↑   |   ↓   |   ←   |   →   |   ↔   |   ;   |   '   |           |           |           |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |       |           |           |   ⌊   |   ⌈   |   ≠   |   ≃   |   ≡   |   ≤   |   ≥   |       |       |       |           |           |       |       |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |       |       |       |           |       |           |           |       |           |           |       |           |       |       |       |       |#|       |       |       |       |
     * `-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_FRONT] = LAYOUT_h7v3_183(
        FT,             FT,               FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,               FT,             FT,
        FT,             FT,               FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,               FT,             FT,
        FT,     FT,     FT,     FT,       FT,             FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,               FT,     FT,     FT,     FT,

        FT,     FT,     FT,     FT,       FT,         FRT_DQO,FRT_COL,FRT_1,  FRT_2,  FRT_3,  FRT_4,  FRT_5,  FRT_6,  FRT_7,  FRT_8,  FRT_9,  FRT_0,  FRT_MIN,FRT_EQU,FRT_BSL,FRT_LBR,FRT_RBR,FT,           FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,         FT,         FRT_Q,  FRT_W,  FRT_E,  FRT_R,  FRT_T,  FRT_Y,  FRT_U,  FRT_I,  FRT_O,  FRT_P,  FRT_LPA,FRT_RPA,FT,         FT,         FT,       FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,         FT,         FT,         FRT_A,  FRT_S,  FRT_D,  FRT_F,  FRT_G,  FRT_H,  FRT_J,  FRT_K,  FRT_L,  FRT_SCO,FRT_SQU,FT,         FT,         FT,           FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,     FT,         FT,         FRT_Z,  FRT_X,  FRT_C,  FRT_V,  FRT_B,  FRT_N,  FRT_M,  FRT_COM,FRT_DOT,FRT_SLA,FT,         FT,         FT,     FT,       FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,     FT,     FT,     FT,         FT,     FT,         FT,         FT,     FT,         FT,         FT,     FT,         FT,     FT,     FT,     FT,       FT,     FT,     FT,     FT
    ),

    /* _FN: Function layer, media & LED mods
     * ,-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |               |               |#|               |               |               |               |               |               |               |               |               |               |#|               |     Reset     |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |               |               |#|               |               |               |               |               |               |               |               |               |               |#|               |               |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|               |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |               |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###################################################################################################################################################################################################################################|
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|           |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |       |           |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |           |           |       |UC_M_WI|       |       |       |       |       |       |       |       |       |       |           |           |       |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|           |  UC_MOD   |           |       |       |       |       |       |       |       |       |UC_M_LN|       |       |           |           |           |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |H_LOCK |#|       |       |           |           |       |       |UC_M_WC|       |       |       |UC_M_MA|       |       |       |           |           |       |       |#|       |       |       |       |
     * |-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |       |       |       |       |#|       |       |       |       |           |       |           |           |       |           |           |       |           |       |       |       |       |#|       |       |       |       |
     * `-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_FN] = LAYOUT_h7v3_183(
        FT,             FT,               FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,               FT,             RESET,
        FT,             FT,               FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,             FT,               FT,             FT,
        FT,     FT,     FT,     FT,       FT,             FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,               FT,     FT,     FT,     FT,

        FT,     FT,     FT,     FT,       FT,         FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,           FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,         FT,         FT,     UC_M_WI,FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,         FT,         FT,       FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,         UC_MOD,     FT,         FT,     FT,     FT,     FT,     FT,     FT,     FT,     FT,     UC_M_LN,FT,     FT,     FT,         FT,         FT,           FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,     FT,         FT,         FT,     FT,     UC_M_WC,FT,     FT,     FT,     UC_M_MA,FT,     FT,     FT,     FT,         FT,         FT,     FT,       FT,     FT,     FT,     FT,
        FT,     FT,     FT,     FT,       FT,     FT,     FT,     FT,     FT,         FT,     FT,         FT,         FT,     FT,         FT,         FT,     FT,         FT,     FT,     FT,     FT,       FT,     FT,     FT,     FT
    )
};

/*
 * Register one of the specified unicode codepoints depending on the state
 * of the modifiers. No modifiers = cp0, Shift = cp1.
 */
static bool tap_unicode(uint32_t cp0, uint32_t cp1) {
    uint8_t mods = get_mods();
    clear_mods();
    if (mods & MOD_MASK_SHIFT) {
        register_unicode(cp1);
    } else {
        register_unicode(cp0);
    }
    set_mods(mods);
    return false;
}

/*
 * Register either the specified char or unicode codepoint depending on the
 * state of the modifiers. No modifiers = ch0, Shift = cp1.
 */
static bool tap_char_or_unicode(char ch0, uint32_t cp1) {
    uint8_t mods = get_mods();
    clear_mods();
    if (mods & MOD_MASK_SHIFT) {
        register_unicode(cp1);
    } else {
        send_char(ch0);
    }
    set_mods(mods);
    return false;
}

/*
 * Tap one of the specified characters depending on the state
 * of the modifiers. No modifiers = ch0, Shift = ch1.
 */
static bool tap_char(char ch0, char ch1) {
    uint8_t mods = get_mods();
    clear_mods();
    if (mods & MOD_MASK_SHIFT) {
        send_char(ch1);
    } else {
        send_char(ch0);
    }
    set_mods(mods);
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            // [daughter board] row 1 POS key macros
        case H_HELP:
            SEND_STRING("[HELP]");
            return false;
        case H_MACRO:
            SEND_STRING("[MACRO]");
            return false;
        case H_TERM:
            SEND_STRING("[TERMINAL]");
            return false;
        case H_QUOTE:
            SEND_STRING("[QUOTE]");
            return false;
        case H_OVRST:
            SEND_STRING("[OVERSTRIKE]");
            return false;
        case H_CLRIN:
            SEND_STRING("[CLEAR INPUT]");
            return false;
        case H_CLRSC:
            SEND_STRING("[CLEAR SCREEN]");
            return false;
        case H_HLOUT:
            SEND_STRING("[HOLD OUTPUT]");
            return false;
        case H_STOUT:
            SEND_STRING("[STOP OUTPUT]");
            return false;
        case H_ABORT:
            SEND_STRING(SS_LCTL(SS_TAP(X_C))); // Ctrl-C
            return false;
        case H_BREAK:
            SEND_STRING(SS_LCTL(SS_TAP(X_PAUSE))); // Ctrl-Break
            return false;
        case H_RSUME:
            SEND_STRING(SS_TAP(X_F)SS_TAP(X_G)SS_TAP(X_ENTER)); // fg<enter>
            return false;
        case H_CALL:
            SEND_STRING("[CALL]");
            return false;

            // [daughter board] row 2 POS key macros
        case H_LOCAL:
            SEND_STRING("[LOCAL]");
            return false;
        case H_NETWK:
            SEND_STRING("[NETWORK]");
            return false;
        case H_SYSTM:
            SEND_STRING("[SYSTEM]");
            return false;
        case H_REFSH:
            SEND_STRING(SS_LGUI(SS_TAP(X_R))); // Cmd-R
            return false;
        case H_BUFFR:
            SEND_STRING("[BUFFER]");
            return false;
        case H_SQUAR:
            SEND_STRING("[SQUARE]");
            return false;
        case H_CIRCL:
            SEND_STRING("[CIRCLE]");
            return false;
        case H_TANGL:
            SEND_STRING("[TRIANGLE]");
            return false;
        case H_DIAMD:
            SEND_STRING("[DIAMOND]");
            return false;
        case H_REPT:
            SEND_STRING("[REPEAT]");
            return false;
        case H_XMIT:
            SEND_STRING("[TRANSMIT]");
            return false;
        case H_STAT:
            SEND_STRING("[STATUS]");
            return false;
        case H_SUSP:
            SEND_STRING(SS_LCTL(SS_TAP(X_Z))); // Ctrl-Z
            return false;

            // [daughter board] row 3
        case H_CLOSE:
            SEND_STRING(SS_LGUI(SS_TAP(X_W))); // Cmd-W
            return false;
        case H_OPEN:
            SEND_STRING(SS_LGUI(SS_TAP(X_O))); // Cmd-O
            return false;
        case SYM_QUE: return tap_unicode(0x003FL, 0x00BFL);  // Question Mark / Inverted Question Mark
        case SYM_EXC: return tap_unicode(0x0021L, 0x00A1L);  // Exclamation Mark / Inverted Exclamation Mark
        case SYM_AT:  return tap_unicode(0x0040L, 0x203DL);  // Commercial At / Interrobang
        case SYM_GBP: return tap_unicode(0x00A3L, 0x1F4B7L); // Pound Sign / Banknote with Pound Sign
        case SYM_EUR: return tap_unicode(0x20ACL, 0x1F4B6L); // Euro Sign / Banknote with Euro Sign
        case SYM_JPY: return tap_unicode(0x00A5L, 0x1F4B4L); // Fullwidth Yen Sign / Banknote with Yen Sign
        case SYM_BTK: return tap_unicode(0x2018L, 0x2032L);  // Left Single Quotation Mark / Prime
        case SYM_DQO: return tap_unicode(0x201CL, 0x2033L);  // Left Double Quotation Mark / Double Prime
        case SYM_DQC: return tap_unicode(0x201DL, 0x2036L);  // Right Double Quotation Mark / Reversed Double Prime
        case SYM_PRI: return tap_unicode(0x2019L, 0x2035L);  // Right Single Quotation Mark / Reversed Prime
        case SYM_UND: return tap_unicode(0xFF3FL, 0x2017L);  // Fullwidth Low Line / Double Low Line
        case SYM_LCH: return tap_unicode(0x2039L, 0x00ABL);  // Single Left-Pointing Angle Quotation Mark / Left-Pointing Double Angle Quotation Mark
        case SYM_RCH: return tap_unicode(0x203AL, 0x00BBL);  // Single Right-Pointing Angle Quotation Mark / Right-Pointing Double Angle Quotation Mark
        case SYM_BAR: return tap_unicode(0x007CL, 0x2016L);  // Vertical Line / Double Vertical Line
        case SYM_LBR: return tap_unicode(0x007BL, 0x23DEL);  // Left Curly Bracket / Top Curly Bracket
        case SYM_RBR: return tap_unicode(0x007DL, 0x23DFL);  // Right Curly Bracket / Bottom Curly Bracket
        case H_COMPL:
            SEND_STRING(SS_TAP(X_TAB)SS_TAP(X_TAB)); // Tab-Tab
            return false;

            // [main board] row 1
        case H_WRITE:
            SEND_STRING(SS_LGUI(SS_TAP(X_S)));
            return false;
        case H_FIND:
            SEND_STRING(SS_LGUI(SS_TAP(X_F)));
            return false;
        case H_DQPM: return tap_char_or_unicode('"', 0x00B1L); // Plus-Minus Sign
        case H_COTI: return tap_char(':', '~');
        case H_LBLC: return tap_char_or_unicode('{', 0x2329L); // Left-Pointing Angle Bracket
        case H_RBRC: return tap_char_or_unicode('}', 0x232AL); // Right-Pointing Angle Bracket
        case H_UNDO2:
            SEND_STRING(SS_LGUI(SS_TAP(X_Z)));
            return false;

            // [main board] row 2
        case H_MARK:
            SEND_STRING("[MARK]");
            return false;
        case H_UNDO:
            SEND_STRING(SS_LGUI(SS_TAP(X_Z)));
            return false;
        case H_PASTE:
            SEND_STRING(SS_LGUI(SS_TAP(X_V)));
            return false;
        case H_CUT:
            SEND_STRING(SS_LGUI(SS_TAP(X_X)));
            return false;
        case H_LPLB: return tap_char('(', '[');
        case H_RPRB: return tap_char(')', ']');

            // [main board] row 3
        case H_SLECT:
            SEND_STRING("[SELECT]");
            return false;
        case H_DEBUG:
            SEND_STRING("[DEBUG]");
            return false;
        case H_SCBT: return tap_char(';', '`');
        case H_LINE:
            SEND_STRING("[LINE]");
            return false;
        case H_PAGE:
            SEND_STRING("[PAGE]");
            return false;

            // [main board] row 4
        case H_TTY:
            SEND_STRING("[TTY]");
            return false;
        case H_LOCK:
            SEND_STRING("[LOCK]");
            return false;

            // [main board] row 5
        case H_EOF:
            SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
            return false;
        case H_7BIT:
            SEND_STRING("[7BIT]");
            return false;
        case H_SMCIR:
            SEND_STRING("[CIRCLE SM]");
            return false;

        // "TOP" symbols
        case TOP_Q:   return tap_unicode(0x2227L, 0x2227L); // Logical And
        case TOP_W:   return tap_unicode(0x2228L, 0x2228L); // Logical Or
        case TOP_E:   return tap_unicode(0x222AL, 0x222AL); // Union
        case TOP_R:   return tap_unicode(0x2229L, 0x2229L); // Intersection
        case TOP_T:   return tap_unicode(0x2282L, 0x2282L); // Subset Of
        case TOP_Y:   return tap_unicode(0x2283L, 0x2283L); // Superset Of
        case TOP_U:   return tap_unicode(0x2200L, 0x2200L); // For All
        case TOP_I:   return tap_unicode(0x221EL, 0x221EL); // Infinity
        case TOP_O:   return tap_unicode(0x2203L, 0x2203L); // There Exists
        case TOP_P:   return tap_unicode(0x2202L, 0x2202L); // Partial Differential
        case TOP_A:   return tap_unicode(0x22A5L, 0x22A5L); // Up Tack
        case TOP_S:   return tap_unicode(0x22A4L, 0x22A4L); // Down Tack
        case TOP_D:   return tap_unicode(0x22A2L, 0x22A2L); // Right Tack
        case TOP_F:   return tap_unicode(0x22A3L, 0x22A3L); // Left Tack
        case TOP_G:   return tap_unicode(0x2191L, 0x2191L); // Upwards Arrow
        case TOP_H:   return tap_unicode(0x2193L, 0x2193L); // Downwards Arrow
        case TOP_J:   return tap_unicode(0x2190L, 0x2190L); // Leftwards Arrow
        case TOP_K:   return tap_unicode(0x2192L, 0x2192L); // Rightwards Arrow
        case TOP_L:   return tap_unicode(0x2194L, 0x2194L); // Left Right Arrow
        case TOP_Z:   return tap_unicode(0x230AL, 0x230AL); // Left Floor
        case TOP_X:   return tap_unicode(0x2308L, 0x2308L); // Left Ceiling
        case TOP_C:   return tap_unicode(0x2260L, 0x2260L); // Not Equal To
        case TOP_V:   return tap_unicode(0x2243L, 0x2243L); // Asymptotically Equal To
        case TOP_B:   return tap_unicode(0x2261L, 0x2261L); // Identical To
        case TOP_N:   return tap_unicode(0x2264L, 0x2264L); // Less-Than or Equal To
        case TOP_M:   return tap_unicode(0x2265L, 0x2265L); // Greater-Than or Equal To

        // "FRONT" symbols
        case FRT_COL: return tap_unicode(0x00A7L, 0x00A7L); // Section Mark
        case FRT_1:   return tap_unicode(0x2020L, 0x2021L); // Dagger / Double Dagger
        case FRT_2:   return tap_unicode(0x2021L, 0x2020L); // Double Dagger / Dagger
        case FRT_3:   return tap_unicode(0x2207L, 0x2206L); // Nabla / Increment
        case FRT_4:   return tap_unicode(0x00A2L, 0x00A2L); // Cent Sign
        case FRT_5:   return tap_unicode(0x00B0L, 0x00B0L); // Degree
        case FRT_6:   return tap_unicode(0x25AFL, 0x25AFL); // White Vertical Rectangle
        case FRT_7:   return tap_unicode(0x00F7L, 0x00F7L); // Division Sign
        case FRT_8:   return tap_unicode(0x00D7L, 0x00D7L); // Multiplication Sign
        case FRT_9:   return tap_unicode(0x00B6L, 0x00B6L); // Pilcrow
        case FRT_0:   return tap_unicode(0x25CBL, 0x25CBL); // White Circle
        case FRT_MIN: return tap_unicode(0x2014L, 0x2013L); // Em Dash / En Dash
        case FRT_EQU: return tap_unicode(0x2248L, 0x2248L); // Almost Equal To
        case FRT_BSL: return tap_unicode(0x2016L, 0x2016L); // Double Vertical Line
        case FRT_LBR: return tap_unicode(0x231EL, 0x231CL); // Bottom Left corner / Top Left Corner
        case FRT_RBR: return tap_unicode(0x231FL, 0x231DL); // Bottom Right Corner / Top Right Corner
        case FRT_Q:   return tap_unicode(0x03B8L, 0x0398L); // Greek Small Letter Theta / Capital
        case FRT_W:   return tap_unicode(0x03C9L, 0x03A9L); // Greek Small Letter Omega / Capital
        case FRT_E:   return tap_unicode(0x03B5L, 0x0395L); // Greek Small Letter Epsilon / Capital
        case FRT_R:   return tap_unicode(0x03C1L, 0x03A1L); // Greek Small Letter Rho / Capital
        case FRT_T:   return tap_unicode(0x03C4L, 0x03A4L); // Greek Small Letter Tau / Capital
        case FRT_Y:   return tap_unicode(0x03C8L, 0x03A8L); // Greek Small Letter Psi / Capital
        case FRT_U:   return tap_unicode(0x03C5L, 0x03A5L); // Greek Small Letter Upsilon / Capital
        case FRT_I:   return tap_unicode(0x03B9L, 0x0399L); // Greek Small Letter Iota / Capital
        case FRT_O:   return tap_unicode(0x03BFL, 0x039FL); // Greek Small Letter Omicron / Capital
        case FRT_P:   return tap_unicode(0x03C0L, 0x03A0L); // Greek Small Letter Pi / Capital
        case FRT_LPA: return tap_unicode(0x27E6L, 0x27E6L); // Mathematical Left White Square Bracket
        case FRT_RPA: return tap_unicode(0x27E7L, 0x27E7L); // Mathematical Right White Square Bracket
        case FRT_A:   return tap_unicode(0x03B1L, 0x0391L); // Greek Small Letter Alpha / Capital
        case FRT_S:   return tap_unicode(0x03C3L, 0x03A3L); // Greek Small Letter Sigma / Capital
        case FRT_D:   return tap_unicode(0x03B4L, 0x0394L); // Greek Small Letter Delta / Capital
        case FRT_F:   return tap_unicode(0x03C6L, 0x03A6L); // Greek Small Letter Phi / Capital
        case FRT_G:   return tap_unicode(0x03B3L, 0x0393L); // Greek Small Letter Gamma / Capital
        case FRT_H:   return tap_unicode(0x03B7L, 0x0397L); // Greek Small Letter Eta / Capital
        case FRT_J:   return tap_unicode(0x03F3L, 0x037FL); // Greek Small Letter Yot / Capital
        case FRT_K:   return tap_unicode(0x03BAL, 0x039AL); // Greek Small Letter Kappa / Capital
        case FRT_L:   return tap_unicode(0x03BBL, 0x039BL); // Greek Small Letter Lambda / Capital
        case FRT_SCO: return tap_unicode(0x00A8L, 0x00A8L); // Diaresis
        case FRT_SQU: return tap_unicode(0x2022L, 0x2023L); // Bullet / Triangular Bullet
        case FRT_Z:   return tap_unicode(0x03B6L, 0x0396L); // Greek Small Letter Zeta / Capital
        case FRT_X:   return tap_unicode(0x03BEL, 0x039EL); // Greek Small Letter Xi / Capital
        case FRT_C:   return tap_unicode(0x03C7L, 0x03A7L); // Greek Small Letter Chi / Capital
        case FRT_V:   return tap_unicode(0x03C2L, 0x03C2L); // Greek Small Letter Final Sigma
        case FRT_B:   return tap_unicode(0x03B2L, 0x0392L); // Greek Small Letter Beta / Capital
        case FRT_N:   return tap_unicode(0x03BDL, 0x039DL); // Greek Small Letter Nu / Capital
        case FRT_M:   return tap_unicode(0x03BCL, 0x039CL); // Greek Small Letter Mu / Capital
        case FRT_COM: return tap_unicode(0x226AL, 0x22D8L); // Much Less-Than / Very Much Less-Than
        case FRT_DOT: return tap_unicode(0x226BL, 0x22D9L); // Much Greater-Than / Very Much Greater-Than
        case FRT_SLA: return tap_unicode(0x222BL, 0x222CL); // Integral / Double Integral
        }
    }

    return true;
};

bool led_update_kb(led_t led_state) {
  // stub
  return true;
};
