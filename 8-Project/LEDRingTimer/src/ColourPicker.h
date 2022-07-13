/*
 * ColourPicker.h
 *
 * Special animation to select a new colour
 * Moves through setting red, green and blue steps
 *
 *  Created on: 3 Jul 2022
 *      Author: jondurrant
 */

#ifndef LEDRINGPROJECT_SRC_COLOURPICKER_H_
#define LEDRINGPROJECT_SRC_COLOURPICKER_H_

#include "RingAnimation.h"

enum ColourToPick {PickRed, PickGreen, PickBlue};

class ColourPicker : public RingAnimation{
public:
	/***
	 * Default constructor
	 * Should use setStrip, setColour and setStepsMS after construction
	 */
	ColourPicker();

	/***
	 * Constructor
	 * @param strip - LED Strip
	 * @param length - Number of LEDs in the strip
	 * @param colour - colour to start with
	 * @param stepMS - Animation speed of a step
	 */
	ColourPicker(
		PicoLed::PicoLedController *strip,
		uint8_t length,
		PicoLed::Color colour,
		uint16_t stepMS);


	/***
	 * Destructor
	 */
	virtual ~ColourPicker();

	/***
	 * Reset animation to start position
	 */
	virtual void reset();

	/***
	 * Set which colour we are picking
	 * @param p - PickRed, PickGreen, PickBlue
	 */
	void setColourToPick(ColourToPick p);

	/***
	 * Get current colour, this may have been updated by the animation
	 * @return
	 */
	PicoLed::Color getColour();

	/***
	 * Increment current component (RGB) of colour by the delta if possible
	 * @param delta
	 */
	void incrementColour(uint8_t delta);

	/***
	 * Decrement current component (RGB) of colour by the delta if possible
	 * @param delta
	 */
	void derementColour(uint8_t delta);

protected:
	/***
	 * Perform step of animation
	 */
	virtual void step();

private:
	//Current colour being picked
	ColourToPick xPick = PickRed;

};

#endif /* LEDRINGPROJECT_SRC_COLOURPICKER_H_ */
