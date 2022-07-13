/*
 * SwitchMgr.h
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 *
 *      Manage a SPST switch on a specific GPIO pin.
 *      Notify observers of press of the switch
 *      Manage through Polling strategy
 */

#ifndef SRC_SWITCHMGR_H_
#define SRC_SWITCHMGR_H_

#include "SwitchObserver.h"

//Time switch must be stable as low to consider being a short press
#define SHORT_PRESS_TIME 5 //ms


class SwitchMgr {
public:
	/***
	 * Constructor
	 * @param gp - GPIO that the switch is connected too.
	 */
	SwitchMgr(uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~SwitchMgr();

	/***
	 * Poll - trigger the checking of the switch.
	 * Should be called repeatable by the main loop
	 */
	void poll();

	/***
	 * Set a single object that is observing the switches state
	 * @param obs - Observer object
	 */
	void setObserver(SwitchObserver * obs);

private:
	/***
	 * Handle a short press
	 */
	void handleShortPress();


	//GPIO number for the switch
	uint8_t xGP = 0;

	// True when we have detected a falling edge
	bool xFallingEdge = false;

	//Time falling edge was detected
	uint32_t xFallingTime;

	// True when we have sent notification of current low to observers
	bool xClickSent = false;

	//Observer
	SwitchObserver *pObs = NULL;

};

#endif /* SRC_SWITCHMGR_H_ */
