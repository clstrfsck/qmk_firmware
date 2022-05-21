/* Copyright 2022 customMK
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

#include_next <mcuconf.h>

// So we can use TIM2 for PWM
#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 5

// Used for underglow
#undef STM32_PWM_USE_TIM2 //timer 2 channel 3
#define STM32_PWM_USE_TIM2 TRUE
#define WS2812_PWM_DRIVER PWMD2 // TIMx


// Used for backlight
//#undef STM32_PWM_USE_TIM3 //timer 3 channel 1
//#define STM32_PWM_USE_TIM3 TRUE

// Used for FRAM and flash
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// Used for OLED and/or LCD
#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
// Consistent with pin locations on Promicro etc
#define I2C1_SCL_PIN       B6
#define I2C1_SDA_PIN       B9
