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
	 * @param led1 - GP number for the led1
	 * @param led2 - GP number for led2
	 */
	LedMgr(uint8_t led1, uint8_t led2);

	/***
	 * Destructor
	 */
	virtual ~LedMgr();

	/***
	 * Handle short press of the switch
	 * @param gp - GPIO number which switch is on
	 */
	virtual void handleShortPress(uint8_t gp);

	/***
	 * Handle a short press from the switch
	 * @param gp - GPIO number of the switch
	 */
	virtual void handleLongPress(uint8_t gp);

private:
	//Current state of the LED. False is off
	bool xLed1State = false;
	bool xLed2State = false;

	// LED GPIO PIN
	uint8_t xLed1Pin = PICO_DEFAULT_LED_PIN;
	uint8_t xLed2Pin = PICO_DEFAULT_LED_PIN;
};

#endif /* SRC_LEDMGR_H_ */
