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
LedMgr::LedMgr(uint8_t gp) {
	xLedPin = gp;

	//Initialise the LED and set it's initial state
	gpio_init(xLedPin);
	gpio_set_dir(xLedPin, GPIO_OUT);
	gpio_put(xLedPin, xLedState);

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
	xLedState = ! xLedState;
	gpio_put(xLedPin, xLedState);
}
