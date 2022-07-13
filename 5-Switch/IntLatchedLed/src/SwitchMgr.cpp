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
 * Used by callback static functions
 */
SwitchMgr * SwitchMgr::pSelf = NULL;

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

	//Setup class reference to this object
	SwitchMgr::pSelf = this;

	//Setup Interrupt
	gpio_set_irq_enabled_with_callback(xGP,
		GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
		true,
		SwitchMgr::gpioCallback
	);
}

SwitchMgr::~SwitchMgr() {
	// NOP
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

/***
 * Static Call back function for push switch
 * @param gpio
 * @param events
 */
void SwitchMgr::gpioCallback (uint gpio, uint32_t events){
	if (SwitchMgr::pSelf != NULL){
		SwitchMgr::pSelf->handleGPIO(gpio, events);
	}
}

/***
 * handle GPIO push switch events
 * @param gpio - GPIO number
 * @param events - Event
 */
void SwitchMgr::handleGPIO(uint gpio, uint32_t events){
	//Check callback is for the right GPIO Pin
	if (gpio == xGP){

		//If Falling Edge then collect time
		if ((events & GPIO_IRQ_EDGE_FALL) > 0){
			xFallingTime = to_ms_since_boot (get_absolute_time ());
		}

		//If Rising Edge
		if ((events & GPIO_IRQ_EDGE_RISE) > 0){
			uint32_t stableTime = to_ms_since_boot (get_absolute_time ()) - xFallingTime;
			xFallingTime = 0;

			//If valid length then handle press
			if ( (stableTime > SHORT_PRESS_TIME) &&
				 (stableTime < MAX_PRESS_TIME)){
				handleShortPress();
			}

		}
	}


}
