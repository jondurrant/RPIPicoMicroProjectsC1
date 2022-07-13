/*
 * ChaserTail.h
 *
 * WS2812B ring animation to run a chaser with a dimmed tail
 * around the ring
 *
 *  Created on: 15 Jun 2022
 *      Author: jondurrant
 */

#ifndef WS2812B_ASSIGNMENTCHASERTAIL_SRC_CHASERTAIL_H_
#define WS2812B_ASSIGNMENTCHASERTAIL_SRC_CHASERTAIL_H_

#include "RingAnimation.h"

class ChaserTail : public RingAnimation{
public:
	/***
	 * Default constructor
	 * SetStrip must be called after this
	 */
	ChaserTail();

	/***
	 * Construct the object
	 * @param strip - PicoLed strip object
	 * @param length - number of RGB LED in strip
	 * @param colour - colour to use for the animation
	 * @param stepMS - time in milliseconds between each step of animation
	 */
	ChaserTail(
			PicoLed::PicoLedController *strip,
			uint8_t length,
			PicoLed::Color colour,
			uint16_t stepMS);


	/***
	 * Destructor
	 */
	virtual ~ChaserTail();

	/***
	 * Reset animation to start possition
	 */
	virtual void reset();

protected:
	/***
	 * Perform step of animation
	 */
	virtual void step();

private:

	//Step count
	uint8_t xStep = 0;

};

#endif /* WS2812B_ASSIGNMENTCHASERTAIL_SRC_CHASERTAIL_H_ */
