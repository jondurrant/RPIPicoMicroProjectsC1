/*
 * RotEncAgent.cpp
 *
 * Rotary Encoder Switch Management
 * Samples state at 2ms intervals
 *  Created on: 28 Mar 2022
 *      Author: jondurrant
 */

#include "RotEncAgent.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>


/***
 * Constructor
 * @param aGP - GPIO pin for RotEnc A
 * @param bGP - GPIO pin for RotEnc B
 * @param numTicks - numTicks in 360 rotation
 */
RotEncAgent::RotEncAgent(
		uint8_t aGP,
		uint8_t bGP,
		uint8_t numTicks) {
	xAGP=aGP;
	xBGP=bGP;
	xNumTicks = numTicks;

	//Setup A
	gpio_init(xAGP);
	gpio_set_dir(xAGP, GPIO_IN);
	gpio_pull_up (xAGP);


	//Setup B
	gpio_init(xBGP);
	gpio_set_dir(xBGP, GPIO_IN);
	gpio_pull_up (xBGP);


	xLast = gpio_get(xAGP);
	xLast = xLast << 1;
	xLast = (gpio_get(xBGP)) | xLast;
}

/***
 * Destructor
 */
RotEncAgent::~RotEncAgent() {
	// NOP
}


/***
 * Handle rotate
 * @param clockwise - true if clockwise, otherwise counter
 */
void RotEncAgent::handleRotate(bool clockwise){
	if (pObserver != NULL){
		pObserver->rotate(clockwise, xPos, (void *)this);
	}
}


/***
 * poll the RotEnv status
 */
void RotEncAgent::poll(){
	uint8_t c;
	c = gpio_get(xAGP);
	c = c << 1;
	c = (gpio_get(xBGP)) | c;


	if (xCW[xLast] == c){
		xCount++;
		if (xCount > 3){
			xPos++;
			if (xPos == xNumTicks){
				xPos = 0;
			}
			//printf("Clockwise %d %d\n", xPos, xCount);
			handleRotate(true);
			xCount = 0;
		}

		xLast = c;
	}

	if (xCCW[xLast] == c){
		xCount-- ;
		if (xCount < -3){
			xPos--;
			if (xPos == -1){
				xPos = xNumTicks - 1;
			}
			//printf("Withershins %d %d\n", xPos, xCount);
			handleRotate(false);
			xCount = 0;
		}

		xLast = c;
	}

}

/***
 * Get current position of RotEnv
 * @return
 */
int8_t RotEncAgent::getPos(){
	return xPos;
}

/***
 * Set a single observer to RotEnv events
 * @param observer
 */
void RotEncAgent::setObserver(RotEncObserver *observer){
	pObserver = observer;
}
