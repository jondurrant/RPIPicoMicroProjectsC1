/**
 * Jon Durrant.
 *
 * Blink LED on Raspberry PICO
 */

#include "pico/stdlib.h"

#define DELAY 500 // in microseconds

int main() {
    const uint LED_PAD = 2;
    gpio_init(LED_PAD);

    gpio_set_dir(LED_PAD, GPIO_OUT);

    while (true) { // Loop forever
        gpio_put(LED_PAD, 1);
        sleep_ms(DELAY);
        gpio_put(LED_PAD, 0);
        sleep_ms(DELAY);
    }

}
