/* Copyright 2021 Jay Greco
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
#pragma once

#include "config_common.h"

/* Used to set host for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_HOST // Force host mode
// #define KEYBOARD_REMOTE // Force remote mode

// FRAM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A0
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR    4 // 48MHz / 4 = 12MHz; max supported by MB85R64 is 20MHz
#define EXTERNAL_EEPROM_BYTE_COUNT           8192
#define EXTERNAL_EEPROM_PAGE_SIZE            64 // N/A for FRAM, just sets the RAM buffer size
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR       8191

// External flash configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B12
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR    1  // 48MHz; max supported by W25Q128JV is 133MHz
#define EXTERNAL_FLASH_BYTE_COUNT           (16 * 1024 * 1024)  //128Mbit or 16MByte
#define EXTERNAL_FLASH_PAGE_SIZE            256
#define EXTERNAL_FLASH_SPI_TIMEOUT          200000 //datasheet max is 200 seconds for flash chip erase

// SPI Configuration (needed for FRAM and FLASH)
#define SPI_DRIVER        SPID1
#define SPI_SCK_PIN       B3
#define SPI_SCK_PAL_MODE  5
#define SPI_MOSI_PIN      B5
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN      B4
#define SPI_MISO_PAL_MODE 5

// Workaround for freezing after MacOS sleep
#define NO_USB_STARTUP_CHECK

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6E61
#define PRODUCT_ID      0x6060

#define DEVICE_VER      0x0002
#define MANUFACTURER    nullbits
#define PRODUCT         NIBBLE

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
#define MATRIX_MUX_COLS 4

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 10

/* So media keys work on encoder */
#define TAP_CODE_DELAY 16

/*
 * Keyboard Matrix Assignments
 * The nibble uses a demultiplexer for the cols.
 * to free up more IOs for awesomeness!
 * See matrix.c for more details.
*/
#define MATRIX_ROW_PINS { B13, B14, B15, B1, A4 }
#define MATRIX_COL_MUX_PINS { A7, A6, A5, A1 }
#define MATRIX_COL_PINS { }

/* Optional SMT LED pins */
/* example code for WS2812-style underglow */
#define RGB_DI_PIN          B10
#define RGBLED_NUM          10

#define WS2812_PWM_DRIVER   PWMD2
#define WS2812_PWM_CHANNEL  3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM   STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL  3

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP

/* Optional encoder pins */
#define ENCODERS_PAD_A { B0 }
#define ENCODERS_PAD_B { A8 }
