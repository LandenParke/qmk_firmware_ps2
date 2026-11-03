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