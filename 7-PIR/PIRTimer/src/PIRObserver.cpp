/*
 * PIRObserver.cpp
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#include "PIRObserver.h"
#include <stdio.h>

/***
 * Constructor
 */
PIRObserver::PIRObserver() {
	// NOP

}

/***
 * Destructor
 */
PIRObserver::~PIRObserver() {
	// NOP
}

/***
 * Handle PIR Event - Detect
 * @param gp - GPIO number of the PIR
 */
void PIRObserver::handlePIRDetect(uint8_t gp){
	printf("PIR Detect on %d\n", gp);
}

/***
 * Handle PIR Event - Clear
 * @param gp - GPIO number of the PIR
 */
void PIRObserver::handlePIRClear(uint8_t gp){
	printf("PIR Clear on %d\n", gp);
}

