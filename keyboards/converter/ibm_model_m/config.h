/* Copyright 2026 Landen Parke (@LandenParke)
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

#define MATRIX_ROWS 20
#define MATRIX_COLS 8

#define BOOTMAGIC_LITE_ROW 14
#define BOOTMAGIC_LITE_COLUMN 6

#define PS2_CLOCK_PIN D1
#define PS2_DATA_PIN D0

#define PS2_INT_INIT() do { \
    EICRA |= (1 << ISC11); \
} while (0)
#define PS2_INT_ON() do { \
    EIMSK |= (1 << INT1); \
} while (0)
#define PS2_INT_OFF() do { \
    EIMSK &= ~(1 << INT1); \
} while (0)
#define PS2_INT_VECT INT1_vect