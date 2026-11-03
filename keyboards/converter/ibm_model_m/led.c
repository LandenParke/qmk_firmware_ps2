#include <stdint.h>
#include "led.h"
#include "ps2.h"

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        uint8_t ps2_led = 0;
        if (led_state.scroll_lock) {
            ps2_led |= 1 << PS2_LED_SCROLL_LOCK;
        }
        if (led_state.num_lock) {
            ps2_led |= 1 << PS2_LED_NUM_LOCK;
        }
        if (led_state.caps_lock) {
            ps2_led |= 1 << PS2_LED_CAPS_LOCK;
        }
        ps2_host_set_led(ps2_led);
    }
    return false;
}