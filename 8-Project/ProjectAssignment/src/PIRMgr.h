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
#include "GPIOObserver.h"

class PIRMgr : public GPIOObserver{
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

	/***
	 * handle GPIO  events
	 * @param gpio - GPIO number
	 * @param events - Event
	 */
	void handleGPIO(uint gpio, uint32_t events);

private:
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
