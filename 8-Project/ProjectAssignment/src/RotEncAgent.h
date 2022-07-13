/*
 * RotEncAgent.h
 *
 * Rotary Encoder Switch Management
 * Using polling strategy
 *
 *  Created on: 20 June 2022
 *      Author: jondurrant
 */

#ifndef ROTENCAGENT_H_
#define ROTENCAGENT_H_

#include <stdint.h>
#include "hardware/gpio.h"
#include "pico/time.h"

#include "RotEncObserver.h"


class RotEncAgent {
public:
	/***
	 * Constructor
	 * @param aGP - GPIO pin for RotEnc A
	 * @param bGP - GPIO pin for RotEnc B
	 * @param numTicks - numTicks in 360 rotation
	 */
	RotEncAgent(
			uint8_t aGP,
			uint8_t bGP,
			uint8_t numTicks);

	/***
	 * Destructor
	 */
	virtual ~RotEncAgent();

	/***
	 * Get current position of RotEnv
	 * @return
	 */
	int8_t getPos();

	/***
	 * Set a single Observer to RotEnv events
	 * @param observer
	 */
	void setObserver(RotEncObserver *observer);

	/***
	 * Poll the RotEnc State
	 */
	void poll();

protected:


	/***
	 * Handle rotate
	 * @param clockwise - true if clockwise, otherwise counter
	 */
	void handleRotate(bool clockwise);


private:

	//Single Observer
	RotEncObserver * pObserver = NULL;

	// GPIO Pad for A & B
	uint8_t xAGP;
	uint8_t xBGP;

	// Number of ticks to track in total rotation
	uint8_t xNumTicks=0;

	// Last position of switches
	uint8_t xLast=0;

	// Count way through the signal
	int8_t xCount=0;

	// Current position
	int16_t xPos = 0;

	//These are lookups for the sequence to see in CW and CCW motion
	uint8_t xCW[4] ={2,0,3,1};
	uint8_t xCCW[4]={1,3,0,2};

};

#endif /* ROTENCAGENT_H_ */
