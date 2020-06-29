/*
Copyright 2020 Martin Sandiford

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

#pragma once

#ifndef I2C_DRIVER
#    define I2C_DRIVER I2CD1
#endif

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x5678
#define DEVICE_VER      0x0001
#define MANUFACTURER dekuNukem
#define PRODUCT kbord
#define DESCRIPTION dekuNukem kbord

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 3

/* direct pins */
#define DIRECT_PINS { { B13, B14, B15 }, { A8, A15, B3 }, { B4, B5, B6 }, { B7, C13, C14 }, { C15, F0, F1 } }

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* OLED */
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_FONT_H          "glcdfont.c"
#define OLED_FONT_START      0
#define OLED_FONT_END        223
#define OLED_FONT_WIDTH      6
#define OLED_FONT_HEIGHT     8
#define OLED_TIMEOUT         60000U
#define OLED_SCROLL_TIMEOUT  1000U
#undef OLED_SCROLL_TIMEOUT_RIGHT
#define OLED_IC              OLED_IC_SSD1306

#define OLED_DISPLAY_CUSTOM
#define OLED_DISPLAY_WIDTH   132
#define OLED_DISPLAY_HEIGHT  64
#define OLED_MATRIX_SIZE     (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#define OLED_BLOCK_TYPE      uint32_t
#define OLED_COM_PINS        COM_PINS_ALT
#define OLED_COLUMN_OFFSET   2

/* I2C */
#define I2C_DRIVER           I2CD1
#define I2C1_SCL_BANK        GPIOB
#define I2C1_SDA_BANK        GPIOB
#define I2C1_SCL             8
#define I2C1_SDA             9

#define I2C1_SCL_PAL_MODE   1U
#define I2C1_SDA_PAL_MODE   1U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH   3U
#define I2C1_TIMINGR_SCLL   9U

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
