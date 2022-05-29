
#include "config.h"
#include "quantum.h"

const uint16_t PROGMEM tkl_keys[] = {
    // Main Keyboard
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_BSLASH,
    KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER,
    KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT,
    KC_LCTRL, KC_LGUI, KC_LALT, KC_SPACE, KC_RALT, KC_RGUI, KC_APPLICATION, KC_RCTRL,

    // System keys
    KC_PSCREEN, KC_SCROLLLOCK, KC_PAUSE,
    // Six-pack
    KC_INSERT, KC_HOME, KC_PGUP,
    KC_DELETE, KC_END,  KC_PGDOWN,
    // Inverted-T
    KC_UP,
    KC_LEFT, KC_DOWN, KC_RIGHT
};

// ** DUMMIES FOR LINKER

void set_single_persistent_default_layer(uint8_t default_layer) {
    abort();
}

void layer_on(uint8_t layer) {
    abort();
}

void layer_off(uint8_t layer) {
    abort();
}

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    abort();
}

bool eeconfig_is_enabled(void) {
    abort();
    return false;
}

void eeconfig_init(void) {
    abort();
}

uint8_t eeconfig_read_keymap(void) {
    abort();
}

void eeconfig_update_keymap(uint8_t val) {
    abort();
}

keymap_config_t keymap_config;

// ** END OF LINKER DUMMIES

size_t find(uint16_t code, const uint16_t *codes, size_t num_codes) {
    size_t i = 0;
    while (i < num_codes) {
        if (codes[i] == code)
            break;
        i += 1;
    }
    return i;
}

#undef dprintf

#include <stdio.h>

int main(int argc, char ** argv) {
    const size_t num_keys = sizeof(tkl_keys)/sizeof(tkl_keys[0]);
    bool foundkeys[num_keys];

    for (int i = 0; i < num_keys; ++i)
        foundkeys[i] = false;
    // appreciate that this is horribly inefficient
    for (int layer = 0; layer < 7; ++layer) {
        for (int row = 0; row < MATRIX_ROWS; ++row) {
            for (int col = 0; col < MATRIX_COLS; ++col) {
                uint16_t keycode = keymaps[layer][row][col] & 0xFF;
                size_t found_index = find(keycode, tkl_keys, num_keys);
                if (found_index < num_keys)
                    foundkeys[found_index] = true;
            }
        }
    }
    for (int i = 0; i < num_keys; ++i) {
        if (!foundkeys[i])
            printf("Can't find TKL %d (%04X)\n", tkl_keys[i], tkl_keys[i]);
    }
    return 0;
}
