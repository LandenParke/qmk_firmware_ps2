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
#include <stdbool.h>
#include <stdint.h>
#include "matrix.h"
#include "ps2.h"

#define ROW(code) ((code) >> 3)
#define COL(code) ((code) & 0x07)

static uint8_t matrix[MATRIX_ROWS];
static bool break_pending;
static bool extended_pending;
static bool pause_release_pending;

void matrix_clear(void);

static uint8_t extended_code(uint8_t code) {
    switch (code) {
        case 0x11: return 0x88;
        case 0x14: return 0x89;
        case 0x1F: return 0x8A;
        case 0x27: return 0x8B;
        case 0x2F: return 0x8C;
        case 0x4A: return 0x8D;
        case 0x5A: return 0x8E;
        case 0x69: return 0x8F;
        case 0x6B: return 0x90;
        case 0x6C: return 0x91;
        case 0x70: return 0x92;
        case 0x71: return 0x93;
        case 0x72: return 0x94;
        case 0x74: return 0x95;
        case 0x75: return 0x96;
        case 0x7A: return 0x97;
        case 0x7C: return 0x99;
        case 0x7D: return 0x98;
        default: return 0xFF;
    }
}

static void set_key(uint8_t code, bool pressed) {
    uint8_t row = ROW(code);
    uint8_t col = COL(code);
    if (row >= MATRIX_ROWS) {
        return;
    }

    if (pressed) {
        matrix[row] |= 1 << col;
    } else {
        matrix[row] &= ~(1 << col);
    }
}

void matrix_init(void) {
    matrix_clear();
    ps2_host_init();
}

uint8_t matrix_scan(void) {
    static uint8_t pause_index;
    static const uint8_t pause_sequence[] = {0x14, 0x77, 0xE1, 0xF0, 0x14, 0xF0, 0x77};
    uint8_t code;

    if (pause_release_pending) {
        set_key(0x9A, false);
        pause_release_pending = false;
    }

    code = ps2_host_recv();
    if (!code) {
        return 0;
    }

    if (pause_index) {
        if (code == pause_sequence[pause_index - 1]) {
            if (++pause_index > sizeof(pause_sequence)) {
                set_key(0x9A, true);
                pause_release_pending = true;
                pause_index = 0;
            }
        } else {
            pause_index = 0;
        }
        return 1;
    }

    if (code == 0xE1) {
        pause_index = 1;
        break_pending = false;
        extended_pending = false;
        return 1;
    }
    if (code == 0xE0) {
        extended_pending = true;
        return 1;
    }
    if (code == 0xF0) {
        break_pending = true;
        return 1;
    }

    if (extended_pending && (code == 0x12 || code == 0x59)) {
        extended_pending = false;
        break_pending = false;
        return 1;
    }

    if (extended_pending) {
        code = extended_code(code);
    }
    if (code != 0xFF) {
        set_key(code, !break_pending);
    }

    break_pending = false;
    extended_pending = false;
    return 1;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1 << col)) != 0;
}

void matrix_clear(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = 0;
    }
}

void matrix_print(void) {
}