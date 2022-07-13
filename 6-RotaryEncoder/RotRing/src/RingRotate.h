/*
 * RingRotate.h
 *
 * Drive LED Ring (WS2812B) base don Rotary Encoder value
 *
 *  Created on: 20 Jun 2022
 *      Author: jondurrant
 */

#ifndef ROTENC_ROTRING_SRC_RINGROTATE_H_
#define ROTENC_ROTRING_SRC_RINGROTATE_H_

#include "RotEncObserver.h"
#include <PicoLed.hpp>

class RotaryDial : public RotEncObserver {
public:
	/***
	 * Constructor
	 * @param strip - Pointer to PicLed controller
	 * @param length - Length of strip
	 * @param colour - Colour to use
	 */
	RotaryDial(
			PicoLed::PicoLedController *strip,
			uint8_t length,
			PicoLed::Color colour);

	/***
	 * Distructor
	 */
	virtual ~RotaryDial();

	/***
	 * Notification of rotation
	 * @param clockwise - Direction. True if clockwise
	 * @param pos - Current possition (within 360)
	 * @param rotEnc - Ref to RotEnc in case multiple being used
	 */
	virtual void rotate(bool clockwise, int16_t pos, void * rotEnc);

	/***
	 * Set the LED strip to use
	 * @param strip - PicoLed strip object
	 * @param length - number of RGB LED in strip
	 */
	virtual void setStrip(PicoLed::PicoLedController *strip, uint8_t length);

	/***
	 * Set the base colour to use for the animation
	 * @param colour
	 */
	virtual void setColour(PicoLed::Color colour);

private:

	// LED Strip
	PicoLed::PicoLedController *pStrip = NULL;

	// Base colour for the animation
	PicoLed::Color xColour = PicoLed::RGB(255,255, 255);

	// length of strip
	uint8_t xLength = 0;

};

#endif /* ROTENC_ROTRING_SRC_RINGROTATE_H_ */
