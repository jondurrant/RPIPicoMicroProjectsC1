/*
 * LedMgr.cpp
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 */

#include "LedMgr.h"

/***
 * Constructor
 */
LedMgr::LedMgr(uint8_t led1, uint8_t led2) {
	//Initialise the LED 1 and set it's initial state
	xLed1Pin = led1;
	gpio_init(xLed1Pin);
	gpio_set_dir(xLed1Pin, GPIO_OUT);
	gpio_put(xLed1Pin, xLed1State);

	//Initialise the LED 2 and set it's initial state
	xLed2Pin = led2;
	gpio_init(xLed2Pin);
	gpio_set_dir(xLed2Pin, GPIO_OUT);
	gpio_put(xLed2Pin, xLed2State);
}

/***
 * Destructor
 */
LedMgr::~LedMgr() {
	// NOP
}

/***
 * Handle short press switch event
 * @param gp - GPIO pin number
 */
void LedMgr::handleShortPress(uint8_t gp){
	//Swap state of the LED and output it to the PIN
	xLed1State = ! xLed1State;
	gpio_put(xLed1Pin, xLed1State);
}


/***
 * Handle short press from switch
 * @param gp - GPIO number of the switch
 */
void LedMgr::handleLongPress(uint8_t gp){
	//Swap state of the LED and output it to the PIN
	xLed2State = ! xLed2State;
	gpio_put(xLed2Pin, xLed2State);
}
