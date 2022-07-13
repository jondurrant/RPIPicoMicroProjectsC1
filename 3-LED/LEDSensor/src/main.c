/**
 * Jon Durrant.
 *
 * Blink LED on Raspberry PICO
 */

#include "pico/stdlib.h"
#include <stdio.h>

#define DELAY 1000 // in microseconds

int main() {
	absolute_time_t start;
	absolute_time_t end;
	int64_t time64;
	int32_t time;
	uint8_t c;

	stdio_init_all();

	sleep_ms(3000);
	printf("GO\n");

    const uint LED_PIN = 2;
    gpio_init(LED_PIN);

    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) { // Loop forever


    	gpio_set_dir(LED_PIN, GPIO_OUT);
        gpio_put(LED_PIN, 1);
        sleep_ms(DELAY);
        printf("Start\n");

        start = end = get_absolute_time();
        //gpio_put(LED_PIN, 0);
        gpio_set_dir(LED_PIN, GPIO_IN);
        while (true){
        	c = gpio_get(LED_PIN);
        	if (c == 0){
        		end = get_absolute_time();
        		break;
        	}
        }

       time64 = absolute_time_diff_us(start, end);
       time = time64;
       printf("Time = %d\n", time);

    }

}
