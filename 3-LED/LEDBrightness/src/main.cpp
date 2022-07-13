/*
 * main.cpp
 *
 *  Created on: 9 Jun 2022
 *      Author: jondurrant
 */

#include "LED.h"

#define DELAY 500 // in microseconds

#define LED_PAD 2 // GP2


int main(){

	LED led(LED_PAD);

	while (true){
		// Loop through 16 different brightness levels
		for (uint8_t i = 0; i <=16; i++){
			uint8_t brightness = 0;
			if (i > 0) {
				brightness = (i * 16) - 1;
			}
			led.setBrightness(brightness);

			sleep_ms(DELAY);
		}
	}
}


