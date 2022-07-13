/*
 * PIRMgr.h
 *
 * Manage the PIR Device.
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#ifndef PIR_PIRLED_SRC_PIRMGR_H_
#define PIR_PIRLED_SRC_PIRMGR_H_

#include "PIRObserver.h"

class PIRMgr {
public:
	/***
	 * Constructor
	 * @param gp - GPIO that the PIR is connected too.
	 */
	PIRMgr(uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~PIRMgr();

	/***
	 * Set a single object that is observing the PIR state
	 * @param obs - Observer object
	 */
	void setObserver(PIRObserver * obs);

private:
	/***
	 * handle GPIO  events
	 * @param gpio - GPIO number
	 * @param events - Event
	 */
	void handleGPIO(uint gpio, uint32_t events);

	/***
	 * Call back function
	 * @param gpio
	 * @param events
	 */
	static void gpioCallback (uint gpio, uint32_t events);

	//Used for call back functions to find the object
	static PIRMgr * pSelf;


	/***
	 * Handle a PIR event
	 * @param start - true if start event, false if cleared
	 */
	void handleEvent(bool start);


	// PAD of the PIR
	uint8_t xGP = 0;

	//Observer
	PIRObserver *pObserver = NULL;
};

#endif /* PIR_PIRLED_SRC_PIRMGR_H_ */
