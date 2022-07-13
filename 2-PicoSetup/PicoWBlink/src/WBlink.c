/**
 * Jon Durrant.
 *
 * Blink LED on Raspberry PICO W
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/cyw43_arch.h"

#define DELAY 500 // in microseconds

int main() {
	stdio_init_all();
	if (cyw43_arch_init()) {
		printf("cyw43 init failed");
	} else {

		while (true) { // Loop forever
			cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
			sleep_ms(DELAY);
			cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
			sleep_ms(DELAY);
		}
	}
}
