/*
 * PIRObserver.h
 * Observer class for PIR
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#ifndef PIR_PIRLED_SRC_PIROBSERVER_H_
#define PIR_PIRLED_SRC_PIROBSERVER_H_

#include "pico/stdlib.h"

class PIRObserver {
public:
	PIRObserver();
	virtual ~PIRObserver();

	/***
	 * Handle PIR Event Detect
	 * @param gp - GPIO number of the PIR
	 */
	virtual void handlePIRDetect(uint8_t gp);

	/***
	 * Handle PIR Event Clear
	 * @param gp - GPIO number of the PIR
	 */
	virtual void handlePIRClear(uint8_t gp);
};

#endif /* PIR_PIRLED_SRC_PIROBSERVER_H_ */
