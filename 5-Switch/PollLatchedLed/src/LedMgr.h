/*
 * LedMgr.h
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 *
 *      Simple class to manage the onboard LED and short presses from a switch
 */

#ifndef SRC_LEDMGR_H_
#define SRC_LEDMGR_H_

#include "SwitchObserver.h"

class LedMgr : public SwitchObserver {
public:
	/***
	 * Constructor
	 * @param gp - GPIO number for the LED
	 */
	LedMgr(uint8_t gp=0);
	/***
	 * Destructor
	 */
	virtual ~LedMgr();

	/***
	 * Handle short press of the switch
	 * @param gp - GPIO number which switch is on
	 */
	virtual void handleShortPress(uint8_t gp);

private:
	//Current state of the LED. False is off
	bool xLedState = false;

	// LED GPIO PIN
	uint8_t xLedPin = 0;
};

#endif /* SRC_LEDMGR_H_ */
