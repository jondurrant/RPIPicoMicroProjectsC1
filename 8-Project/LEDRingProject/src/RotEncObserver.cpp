/*
 * RotEncListener.cpp
 *
 * Abstract listener for the RotEnc
 *
 *  Created on: 20 June 2022
 *      Author: jondurrant
 */

#include "RotEncObserver.h"

#include <stdio.h>

/***
 * Constructor
 */
RotEncObserver::RotEncObserver() {
	// NOP

}

/***
 * Destructor
 */
RotEncObserver::~RotEncObserver() {
	// NOP
}

/***
 * Notification of rotation
 * @param clockwise - Direction. True if clockwise
 * @param pos - Current position (within 360)
 * @param rotEnc - Ref to RotEnc in case multiple being used
 */
void RotEncObserver::rotate(bool clockwise, int16_t pos, void * rotEnc){
	if (clockwise){
		printf("Clockwise %d\n", pos);
	} else {
		printf("Withershins %d\n", pos);
	}
}
