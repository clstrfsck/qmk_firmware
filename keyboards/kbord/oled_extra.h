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

#include "oled_driver.h"

// Set or clear pixel at x,y location
void oled_set_pixel(uint16_t x, uint16_t y);
void oled_clear_pixel(uint16_t x, uint16_t y);

// Draw horizontal line at y between x1 and x2
void oled_draw_hline(uint16_t x1, uint16_t x2, uint16_t y);
void oled_clear_hline(uint16_t x1, uint16_t x2, uint16_t y);

// Draw vertical line at x between y1 and y2
void oled_draw_vline(uint16_t x, uint16_t y1, uint16_t y2);
void oled_clear_vline(uint16_t x, uint16_t y1, uint16_t y2);

// Draw arbitrary line
void oled_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
