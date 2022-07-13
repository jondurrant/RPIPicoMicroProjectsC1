/*
 * PIRMgr.cpp
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#include "PIRMgr.h"
#include <cstddef>
#include "pico/stdlib.h"
#include <stdlib.h>
#include "hardware/gpio.h"

PIRMgr * PIRMgr::pSelf = NULL;

/***
 * Constructor
 * @param gp - GPIO that the switch is connected too.
 */
PIRMgr::PIRMgr(uint8_t gp){
	xGP = gp;

	//Initialise the GPIO pin
	gpio_init(xGP);
	gpio_set_dir(xGP, GPIO_IN);

	//Setup class reference to this object
	PIRMgr::pSelf = this;

	//Setup Interrupt
	gpio_set_irq_enabled_with_callback(xGP,
		GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
		true,
		PIRMgr::gpioCallback
	);
}

/***
 * Destructor
 */
PIRMgr::~PIRMgr() {
	// NOP
}

/***
 * Set a single object that is observing the PIR state
 * @param obs - Observer object
 */
void PIRMgr::setObserver(PIRObserver * obs){
	pObserver = obs;
}


/***
 * Handle a PIR event
 * @param start - true if start event, false if cleared
 */
void PIRMgr::handleEvent(bool start){
	if (pObserver != NULL){
		if (start){
			pObserver->handlePIRDetect(xGP);
		} else {
			pObserver->handlePIRClear(xGP);
		}
	}
}


/***
 * Static Call back function for PIR
 * @param gpio
 * @param events
 */
void PIRMgr::gpioCallback (uint gpio, uint32_t events){
	if (PIRMgr::pSelf != NULL){
		PIRMgr::pSelf->handleGPIO(gpio, events);
	}
}

/***
 * handle GPIO PIR events
 * @param gpio - GPIO number
 * @param events - Event
 */
void PIRMgr::handleGPIO(uint gpio, uint32_t events){
	//Check callback is for the right GPIO Pin
	if (gpio == xGP){

		//If Falling Edge - Clear event
		if ((events & GPIO_IRQ_EDGE_FALL) > 0){
			handleEvent(false);
		}

		//If Rising Edge - Detect event
		if ((events & GPIO_IRQ_EDGE_RISE) > 0){
			handleEvent(true);
		}
	}

}
