/*
 * PIRLed.h
 * Manage an LED to turn on when detect and off when cleared
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#ifndef PIR_PIRLED_SRC_PIRLED_H_
#define PIR_PIRLED_SRC_PIRLED_H_

#include "PIRObserver.h"
#include <stdio.h>

class PIRLed : public PIRObserver{
public:
	/***
	 * Constructor
	 * @param ledPad - PAD the LED is connected too
	 */
	PIRLed(uint8_t ledPad);

	/***
	 * Destructor
	 */
	virtual ~PIRLed();

	/***
	 * Handle PIR Event
	 * @param gp - GPIO number of the PIR
	 */
	virtual void handlePIRDetect(uint8_t gp);

	/***
	 * Handle PIR Event
	 * @param gp - GPIO number of the PIR
	 */
	virtual void handlePIRClear(uint8_t gp);

private:
	//PAD of the LED
	uint8_t xLEDPad = 0;

};

#endif /* PIR_PIRLED_SRC_PIRLED_H_ */
