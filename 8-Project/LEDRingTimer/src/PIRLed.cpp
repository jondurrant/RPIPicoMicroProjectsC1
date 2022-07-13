/*
 * PIRLed.cpp
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#include "PIRLed.h"

/***
 * Constructor
 * @param ledPad
 */
PIRLed::PIRLed(uint8_t ledPad) {
	xLEDPad = ledPad;

	//Initialise the LED and set it's initial state
	gpio_init(xLEDPad);
	gpio_set_dir(xLEDPad, GPIO_OUT);
	gpio_put(xLEDPad, 0);

}

PIRLed::~PIRLed() {
	// NOP
}


/***
 * Handle PIR Event
 * @param gp - GPIO number of the PIR
 */
void PIRLed::handlePIRDetect(uint8_t gp){
	//Turn on LED
	gpio_put(xLEDPad, 1);
}

/***
 * Handle PIR Event
 * @param gp - GPIO number of the PIR
 */
void PIRLed::handlePIRClear(uint8_t gp){
	//Turn off LED
	gpio_put(xLEDPad, 0);
}
