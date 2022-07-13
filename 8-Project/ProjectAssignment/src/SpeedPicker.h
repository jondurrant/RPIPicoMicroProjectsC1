/*
 * SpeedPicker.h
 *
 *  Created on: 5 Jul 2022
 *      Author: jondurrant
 */

#ifndef PROJECT_PROJECTASSIGNMENT_SRC_SPEEDPICKER_H_
#define PROJECT_PROJECTASSIGNMENT_SRC_SPEEDPICKER_H_

#include "RingAnimation.h"

class SpeedPicker : public RingAnimation{
public:
	/***
	 * Default constructor
	 * Should use setStrip, setColour and setStepsMS after construction
	 */
	SpeedPicker();

	/***
	 * Constructor
	 * @param strip - LED Strip
	 * @param length - Number of LEDs in the strip
	 * @param colour - colour to start with
	 * @param stepMS - Animation speed of a step
	 */
	SpeedPicker(
		PicoLed::PicoLedController *strip,
		uint8_t length,
		PicoLed::Color colour,
		uint16_t stepMS);

	/***
	 * Destructor
	 */
	virtual ~SpeedPicker();

	/***
	 * Reset animation to start position
	 */
	virtual void reset();

	/***
	 * Get Current speed
	 * @return - step speed in milliseconds
	 */
	uint16_t getStepMS();

	/***
	 * Increment speed by delta
	 * @param delta
	 */
	void incrementSpeed(uint16_t delta);

	/***
	 * Decrement speed by delta
	 * @param delta
	 */
	void derementSpeed(uint16_t delta);

protected:
	/***
	 * Perform step of animation
	 */
	virtual void step();

private:

	//Step count
	uint8_t xStep = 0;

};

#endif /* PROJECT_PROJECTASSIGNMENT_SRC_SPEEDPICKER_H_ */
