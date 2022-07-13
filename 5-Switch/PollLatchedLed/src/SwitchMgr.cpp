/*
 * SwitchMgr.cpp
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 */

#include "SwitchMgr.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include "hardware/gpio.h"
#include "pico/time.h"


/***
 * Constructor
 * @param gp - GPIO number for the switch
 */
SwitchMgr::SwitchMgr(uint8_t gp) {
	//Store the GP for later
	xGP = gp;

	//Initialise the GPIO pin
	gpio_init(xGP);
	gpio_pull_up (xGP);
	gpio_set_dir(xGP, GPIO_IN);
}

SwitchMgr::~SwitchMgr() {
	// NOP
}


void SwitchMgr::poll(){
	// Get the switch status
	uint8_t c = gpio_get(xGP);

	if (c == 1){
		//Switch is up or bouncing
		xFallingEdge = false;
		xClickSent = false;
	} else {
		//On Detecting falling edge
		if (!xFallingEdge){
			//First detection of low, so store as falling edge
			xFallingEdge = true;
			xFallingTime = to_ms_since_boot (get_absolute_time ());
		} else {
			//if we have not previous sent the click notification
			if (!xClickSent){
				// Have we been stable for long enough
				uint32_t stableTime = to_ms_since_boot (get_absolute_time ()) - xFallingTime;
				if (stableTime > SHORT_PRESS_TIME){
					xClickSent = true;
					handleShortPress();
				}
			}

		}
	}
}

/***
 * Set single observer of the switch
 * @param obs - observer object
 */
void SwitchMgr::setObserver(SwitchObserver * obs){
	pObs = obs;
}

/***
 * Handle a short press event by notifying the observer
 */
void SwitchMgr::handleShortPress(){
	if (pObs != NULL){
		pObs->handleShortPress(xGP);
	}
}
