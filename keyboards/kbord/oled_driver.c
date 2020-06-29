/*
Copyright 2019 Ryan Caltabiano <https://github.com/XScorpion2>

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
#include "i2c_master.h"
#include "oled_driver.h"
#include OLED_FONT_H
#include "timer.h"
#include "print.h"

#include <string.h>

#include "progmem.h"

// Used commands from spec sheet: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
// for SH1106: https://www.velleman.eu/downloads/29/infosheets/sh1106_datasheet.pdf

// Fundamental Commands
#define CONTRAST 0x81
#define DISPLAY_ALL_ON 0xA5
#define DISPLAY_ALL_ON_RESUME 0xA4
#define NORMAL_DISPLAY 0xA6
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define NOP 0xE3

// Scrolling Commands
#define ACTIVATE_SCROLL 0x2F
#define DEACTIVATE_SCROLL 0x2E
#define SCROLL_RIGHT 0x26
#define SCROLL_LEFT 0x27
#define SCROLL_RIGHT_UP 0x29
#define SCROLL_LEFT_UP 0x2A

// Addressing Setting Commands
#define MEMORY_MODE 0x20
#define COLUMN_ADDR 0x21
#define PAGE_ADDR 0x22

// Hardware Configuration Commands
#define DISPLAY_START_LINE 0x40
#define SEGMENT_REMAP 0xA0
#define SEGMENT_REMAP_INV 0xA1
#define MULTIPLEX_RATIO 0xA8
#define COM_SCAN_INC 0xC0
#define COM_SCAN_DEC 0xC8
#define DISPLAY_OFFSET 0xD3
#define COM_PINS 0xDA
#define COM_PINS_SEQ 0x02
#define COM_PINS_ALT 0x12
#define COM_PINS_SEQ_LR 0x22
#define COM_PINS_ALT_LR 0x32

// Timing & Driving Commands
#define DISPLAY_CLOCK 0xD5
#define PRE_CHARGE_PERIOD 0xD9
#define VCOM_DETECT 0xDB

// Charge Pump Commands
#define CHARGE_PUMP 0x8D

// Misc defines
#define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#define OLED_BLOCK_SIZE  (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)

// i2c defines
#define I2C_CMD 0x00
#define I2C_DATA 0x40
#define I2C_TRANSMIT(data) i2c_transmit((OLED_DISPLAY_ADDRESS << 1), &data[0], sizeof(data), I2C_TIMEOUT)
#define I2C_WRITE_REG(mode, data, size) i2c_writeReg((OLED_DISPLAY_ADDRESS << 1), mode, data, size, I2C_TIMEOUT)

// Display buffer's is the same as the OLED memory layout
// this is so we don't end up with rounding errors with
// parts of the display unusable or don't get cleared correctly
// and also allows for drawing & inverting
uint8_t         oled_buffer[OLED_MATRIX_SIZE];
uint8_t *       oled_cursor;
OLED_BLOCK_TYPE oled_dirty          = 0;
bool            oled_initialized    = false;
bool            oled_active         = false;
bool            oled_scrolling      = false;
uint8_t         oled_scroll_speed   = 0;  // this holds the speed after being remapped to ssd1306 internal values
uint8_t         oled_scroll_start   = 0;
uint8_t         oled_scroll_end     = 7;
#if OLED_TIMEOUT > 0
uint32_t oled_timeout;
#endif
#if OLED_SCROLL_TIMEOUT > 0
uint32_t oled_scroll_timeout;
#endif

// Internal variables to reduce math instructions

// Flips the rendering bits for a character at the current cursor position
static void InvertCharacter(uint8_t *cursor) {
    const uint8_t *end = cursor + OLED_FONT_WIDTH;
    while (cursor < end) {
        *cursor = ~(*cursor);
        cursor++;
    }
}

bool oled_init(uint8_t rotation) {
    // Rotation not handled just yet
    oled_init_user(rotation);
    i2c_init();

    static const uint8_t PROGMEM display_setup1[] = {
        I2C_CMD,
        DISPLAY_OFF,
        DISPLAY_CLOCK,
        0x80,
        MULTIPLEX_RATIO,
        OLED_DISPLAY_HEIGHT - 1,
        DISPLAY_OFFSET,
        0x00,
        DISPLAY_START_LINE | 0x00,
        CHARGE_PUMP,
        0x14,
        MEMORY_MODE,
        0x00  // Vertical addressing mode
    };
    i2c_status_t cmd_set_1_status = I2C_TRANSMIT(display_setup1);
    if (cmd_set_1_status != I2C_STATUS_SUCCESS) {
        uprintf("oled_init cmd set 1 failed %d\n", cmd_set_1_status);
        return false;
    }

    const uint8_t PROGMEM display_normal[] = {I2C_CMD, SEGMENT_REMAP_INV, COM_SCAN_DEC};
    if (I2C_TRANSMIT(display_normal) != I2C_STATUS_SUCCESS) {
        print("oled_init cmd normal rotation failed\n");
        return false;
    }

    const uint8_t PROGMEM display_setup2[] = {I2C_CMD, COM_PINS, OLED_COM_PINS, CONTRAST, 0x8F, PRE_CHARGE_PERIOD, 0xF1, VCOM_DETECT, 0x40, DISPLAY_ALL_ON_RESUME, NORMAL_DISPLAY, DEACTIVATE_SCROLL, DISPLAY_ON};
    if (I2C_TRANSMIT(display_setup2) != I2C_STATUS_SUCCESS) {
        print("display_setup2 failed\n");
        return false;
    }

#if OLED_TIMEOUT > 0
    oled_timeout = timer_read32() + OLED_TIMEOUT;
#endif
#if OLED_SCROLL_TIMEOUT > 0
    oled_scroll_timeout = timer_read32() + OLED_SCROLL_TIMEOUT;
#endif

    oled_clear();
    oled_initialized = true;
    oled_active      = true;
    oled_scrolling   = false;
    return true;
}

__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) { return rotation; }

void oled_clear(void) {
    memset(oled_buffer, 0, sizeof(oled_buffer));
    oled_cursor = &oled_buffer[OLED_COLUMN_OFFSET];
    oled_dirty  = ~((OLED_BLOCK_TYPE)0);
}

void oled_render(void) {
    // Do we have work to do?
    if (!oled_dirty || oled_scrolling) {
        return;
    }

    for (int i = 0; i < OLED_BLOCK_COUNT; i++) {
        if (oled_dirty & (1UL << i)) {
            // Set column & page position
            uint8_t page = i / sizeof(OLED_BLOCK_TYPE);
            uint8_t offset = (i % sizeof(OLED_BLOCK_TYPE)) * OLED_BLOCK_SIZE;
            uint8_t lnyb = offset & 0x0F;
            uint8_t hnyb = offset >> 4;
            uint8_t display_start[] = { I2C_CMD, 0xB0 + page, 0x00 + lnyb, 0x10 + hnyb };

            // Send column & page position
            if (I2C_TRANSMIT(display_start) != I2C_STATUS_SUCCESS) {
                print("oled_render offset command failed\n");
                return;
            }

            // Send render data chunk as is
            if (I2C_WRITE_REG(I2C_DATA, &oled_buffer[OLED_BLOCK_SIZE * i], OLED_BLOCK_SIZE) != I2C_STATUS_SUCCESS) {
                print("oled_render data failed\n");
                return;
            }
        }
    }

    // Turn on display if it is off
    oled_on();

    // Clear dirty flag
    oled_dirty = 0;
}

void oled_set_cursor(uint8_t col, uint8_t line) {
    uint16_t index = OLED_COLUMN_OFFSET + line * OLED_DISPLAY_WIDTH + col * OLED_FONT_WIDTH;

    // Out of bounds?
    if (index >= OLED_MATRIX_SIZE) {
        index = 0;
    }

    oled_cursor = &oled_buffer[index];
}

void oled_advance_page(bool clearPageRemainder) {
    uint16_t index     = oled_cursor - &oled_buffer[0];
    uint8_t  remaining = OLED_DISPLAY_WIDTH - (index % OLED_DISPLAY_WIDTH);

    if (clearPageRemainder) {
        // Remaining Char count
        remaining = remaining / OLED_FONT_WIDTH;

        // Write empty character until next line
        while (remaining--) oled_write_char(' ', false);
    } else {
        // Next page index out of bounds?
        if (OLED_COLUMN_OFFSET + index + remaining >= OLED_MATRIX_SIZE) {
            index     = OLED_COLUMN_OFFSET;
            remaining = 0;
        }

        oled_cursor = &oled_buffer[index + remaining];
    }
}

void oled_advance_char(void) {
    uint16_t nextIndex      = oled_cursor - &oled_buffer[0] + OLED_FONT_WIDTH;
    uint8_t  remainingSpace = OLED_DISPLAY_WIDTH - (nextIndex % OLED_DISPLAY_WIDTH);

    // Do we have enough space on the current line for the next character
    if (remainingSpace < OLED_FONT_WIDTH) {
        nextIndex += remainingSpace + OLED_COLUMN_OFFSET;
    }

    // Did we go out of bounds
    if (nextIndex >= OLED_MATRIX_SIZE) {
        nextIndex = OLED_COLUMN_OFFSET;
    }

    // Update cursor position
    oled_cursor = &oled_buffer[nextIndex];
}

// Main handler that writes character data to the display buffer
void oled_write_char(const char data, bool invert) {
    // Advance to the next line if newline
    if (data == '\n') {
        // Old source wrote ' ' until end of line...
        oled_advance_page(true);
        return;
    }

    if (data == '\r') {
        oled_advance_page(false);
        return;
    }

    // copy the current render buffer to check for dirty after
    static uint8_t oled_temp_buffer[OLED_FONT_WIDTH];
    memcpy(&oled_temp_buffer, oled_cursor, OLED_FONT_WIDTH);

    _Static_assert(sizeof(font) >= ((OLED_FONT_END + 1 - OLED_FONT_START) * OLED_FONT_WIDTH), "OLED_FONT_END references outside array");

    // set the reder buffer data
    uint8_t cast_data = (uint8_t)data;  // font based on unsigned type for index
    if (cast_data < OLED_FONT_START || cast_data > OLED_FONT_END) {
        memset(oled_cursor, 0x00, OLED_FONT_WIDTH);
    } else {
        const uint8_t *glyph = &font[(cast_data - OLED_FONT_START) * OLED_FONT_WIDTH];
        memcpy(oled_cursor, glyph, OLED_FONT_WIDTH);
    }

    // Invert if needed
    if (invert) {
        InvertCharacter(oled_cursor);
    }

    // Dirty check
    if (memcmp(&oled_temp_buffer, oled_cursor, OLED_FONT_WIDTH)) {
        uint16_t index = oled_cursor - &oled_buffer[0];
        oled_dirty |= (1 << (index / OLED_BLOCK_SIZE));
        // Edgecase check if the written data spans the 2 chunks
        oled_dirty |= (1 << ((index + OLED_FONT_WIDTH) / OLED_BLOCK_SIZE));
    }

    // Finally move to the next char
    oled_advance_char();
}

void oled_write(const char *data, bool invert) {
    const char *end = data + strlen(data);
    while (data < end) {
        oled_write_char(*data, invert);
        data++;
    }
}

void oled_write_ln(const char *data, bool invert) {
    oled_write(data, invert);
    oled_advance_page(true);
}

void oled_pan(bool left) {
    uint16_t i = 0;
    for (uint16_t y = 0; y < OLED_DISPLAY_HEIGHT / 8; y++) {
        if (left) {
            for (uint16_t x = 0; x < OLED_DISPLAY_WIDTH - 1; x++) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i + 1];
            }
        } else {
            for (uint16_t x = OLED_DISPLAY_WIDTH - 1; x > 0; x--) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i - 1];
            }
        }
    }
    oled_dirty = ~((OLED_BLOCK_TYPE)0);
}

void oled_write_raw_byte(const char data, uint16_t index) {
    if (index > OLED_MATRIX_SIZE) index = OLED_MATRIX_SIZE;
    if (oled_buffer[index] == data) return;
    oled_buffer[index] = data;
    oled_dirty |= (1 << (index / OLED_BLOCK_SIZE));
}

void oled_write_raw(const char *data, uint16_t size) {
    if (size > OLED_MATRIX_SIZE) size = OLED_MATRIX_SIZE;
    for (uint16_t i = 0; i < size; i++) {
        if (oled_buffer[i] == data[i]) continue;
        oled_buffer[i] = data[i];
        oled_dirty |= (1 << (i / OLED_BLOCK_SIZE));
    }
}

bool oled_on(void) {
#if OLED_TIMEOUT > 0
    oled_timeout = timer_read32() + OLED_TIMEOUT;
#endif

    static const uint8_t PROGMEM display_on[] = {I2C_CMD, DISPLAY_ON};
    if (!oled_active) {
        if (I2C_TRANSMIT(display_on) != I2C_STATUS_SUCCESS) {
            print("oled_on cmd failed\n");
            return oled_active;
        }
        oled_active = true;
    }
    return oled_active;
}

bool oled_off(void) {
    static const uint8_t PROGMEM display_off[] = {I2C_CMD, DISPLAY_OFF};
    if (oled_active) {
        if (I2C_TRANSMIT(display_off) != I2C_STATUS_SUCCESS) {
            print("oled_off cmd failed\n");
            return oled_active;
        }
        oled_active = false;
    }
    return !oled_active;
}

// Set the specific 8 lines rows of the screen to scroll.
// 0 is the default for start, and 7 for end, which is the entire
// height of the screen.  For 128x32 screens, rows 4-7 are not used.
void oled_scroll_set_area(uint8_t start_line, uint8_t end_line) {
    oled_scroll_start = start_line;
    oled_scroll_end   = end_line;
}

void oled_scroll_set_speed(uint8_t speed) {
    // Sets the speed for scrolling... does not take effect
    // until scrolling is either started or restarted
    // the ssd1306 supports 8 speeds
    // FrameRate2   speed = 7
    // FrameRate3   speed = 4
    // FrameRate4   speed = 5
    // FrameRate5   speed = 0
    // FrameRate25  speed = 6
    // FrameRate64  speed = 1
    // FrameRate128 speed = 2
    // FrameRate256 speed = 3
    // for ease of use these are remaped here to be in order
    static const uint8_t scroll_remap[8] = {7, 4, 5, 0, 6, 1, 2, 3};
    oled_scroll_speed                    = scroll_remap[speed];
}

bool oled_scroll_right(void) {
    // Dont enable scrolling if we need to update the display
    // This prevents scrolling of bad data from starting the scroll too early after init
    if (!oled_dirty && !oled_scrolling) {
        uint8_t display_scroll_right[] = {I2C_CMD, SCROLL_RIGHT, 0x00, oled_scroll_start, oled_scroll_speed, oled_scroll_end, 0x00, 0xFF, ACTIVATE_SCROLL};
        if (I2C_TRANSMIT(display_scroll_right) != I2C_STATUS_SUCCESS) {
            print("oled_scroll_right cmd failed\n");
            return oled_scrolling;
        }
        oled_scrolling = true;
    }
    return oled_scrolling;
}

bool oled_scroll_left(void) {
    // Dont enable scrolling if we need to update the display
    // This prevents scrolling of bad data from starting the scroll too early after init
    if (!oled_dirty && !oled_scrolling) {
        uint8_t display_scroll_left[] = {I2C_CMD, SCROLL_LEFT, 0x00, oled_scroll_start, oled_scroll_speed, oled_scroll_end, 0x00, 0xFF, ACTIVATE_SCROLL};
        if (I2C_TRANSMIT(display_scroll_left) != I2C_STATUS_SUCCESS) {
            print("oled_scroll_left cmd failed\n");
            return oled_scrolling;
        }
        oled_scrolling = true;
    }
    return oled_scrolling;
}

bool oled_scroll_off(void) {
    if (oled_scrolling) {
        static const uint8_t PROGMEM display_scroll_off[] = {I2C_CMD, DEACTIVATE_SCROLL};
        if (I2C_TRANSMIT(display_scroll_off) != I2C_STATUS_SUCCESS) {
            print("oled_scroll_off cmd failed\n");
            return oled_scrolling;
        }
        oled_scrolling = false;
        oled_dirty     = ~((OLED_BLOCK_TYPE)0);
    }
    return !oled_scrolling;
}

uint8_t oled_max_chars(void) {
    return OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH;
}

uint8_t oled_max_lines(void) {
    return OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT;
}

void oled_task(void) {
    if (!oled_initialized) {
        return;
    }

    oled_set_cursor(0, 0);

    oled_task_user();

#if OLED_SCROLL_TIMEOUT > 0
    if (oled_dirty && oled_scrolling) {
        oled_scroll_timeout = timer_read32() + OLED_SCROLL_TIMEOUT;
        oled_scroll_off();
    }
#endif

    // Smart render system, no need to check for dirty
    oled_render();

    // Display timeout check
#if OLED_TIMEOUT > 0
    if (oled_active && timer_expired32(timer_read32(), oled_timeout)) {
        oled_off();
    }
#endif

#if OLED_SCROLL_TIMEOUT > 0
    if (!oled_scrolling && timer_expired32(timer_read32(), oled_scroll_timeout)) {
#    ifdef OLED_SCROLL_TIMEOUT_RIGHT
        oled_scroll_right();
#    else
        oled_scroll_left();
#    endif
    }
#endif
}

__attribute__((weak)) void oled_task_user(void) {}

void oled_set_pixel(uint16_t x, uint16_t y) {
    uint16_t byte = (y >> 3) * OLED_DISPLAY_WIDTH + x;
    if (byte < OLED_MATRIX_SIZE) {
        uint8_t bit = y & 0x07;
        uint8_t mask = (1 << bit);
        uint8_t oldvalue = oled_buffer[byte];
        uint8_t newvalue = oldvalue | mask;
        if (newvalue != oldvalue) {
            oled_buffer[byte] = newvalue;
            oled_dirty |= (1 << (byte / OLED_BLOCK_SIZE));
        }
    }
}

void oled_clear_pixel(uint16_t x, uint16_t y) {
    uint16_t byte = (y >> 3) * OLED_DISPLAY_WIDTH + x;
    if (byte < OLED_MATRIX_SIZE) {
        uint8_t bit = y & 0x07;
        uint8_t mask = (1 << bit);
        uint8_t oldvalue = oled_buffer[byte];
        uint8_t newvalue = oldvalue & (~mask);
        if (newvalue != oldvalue) {
            oled_buffer[byte] = newvalue;
            oled_dirty |= (1 << (byte / OLED_BLOCK_SIZE));
        }
    }
}

void oled_draw_hline(uint16_t x1, uint16_t x2, uint16_t y) {
    // Intention is to improve the performance of this at some point
    for (uint16_t x = x1; x <= x2; ++x) {
        oled_set_pixel(x, y);
    }
}

void oled_clear_hline(uint16_t x1, uint16_t x2, uint16_t y) {
    // Intention is to improve the performance of this at some point
    for (uint16_t x = x1; x <= x2; ++x) {
        oled_clear_pixel(x, y);
    }
}

void oled_draw_vline(uint16_t x, uint16_t y1, uint16_t y2) {
    // Intention is to improve the performance of this at some point
    for (uint16_t y = y1; y <= y2; ++y) {
        oled_set_pixel(x, y);
    }
}

void oled_clear_vline(uint16_t x, uint16_t y1, uint16_t y2) {
    // Intention is to improve the performance of this at some point
    for (uint16_t y = y1; y <= y2; ++y) {
        oled_clear_pixel(x, y);
    }
}

inline int16_t iabs(int16_t value) {
    return (value >= 0) ? value : -value;
}

typedef void (*set_pixel_t)(int16_t x, int16_t y);

void oled_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    int16_t dx = iabs(x2 - x1);
    int16_t sx = x1 < x2 ? 1 : -1;
    int16_t dy = -iabs(y2 - y1);
    int16_t sy = y1 < y2 ? 1 : -1; 
    int16_t err = dx + dy;
 
    while (true) {
        if (x1 >= 0 && x1 < OLED_DISPLAY_WIDTH && y1 >= 0 && y1 < OLED_DISPLAY_HEIGHT) {
            oled_set_pixel(x1, y1);
        }
        if (x1 == x2 && y1 == y2)
            break;
        int16_t e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}
