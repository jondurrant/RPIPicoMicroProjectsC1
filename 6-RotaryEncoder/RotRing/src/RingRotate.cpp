/*
 * RingRotate.cpp
 *
 *  Created on: 20 Jun 2022
 *      Author: jondurrant
 */

#include "RingRotate.h"

/***
 * Constructor
 * @param strip - Pointer to PicLed controller
 * @param length - Length of strip
 * @param colour - Colour to use
 */
RotaryDial::RotaryDial(PicoLed::PicoLedController *strip,
		uint8_t length,
		PicoLed::Color colour) {
	setStrip(strip, length);
	setColour(colour);

	//Initialises to a single LED lit
	if (pStrip != NULL){
		pStrip->clear();
		pStrip->setPixelColor(0, xColour);
		pStrip->show();
	}
}


/***
 * Distructor
 */
RotaryDial::~RotaryDial(){
	//NOP
}



/***
 * Set the LED strip to use
 * @param strip - PicoLed strip object
 * @param length - number of RGB LED in strip
 */
void RotaryDial::setStrip(
		PicoLed::PicoLedController *strip,
		uint8_t length){
	pStrip  = strip;
	xLength = length;
}



/***
 * Set the base colour to use for the animation
 * @param colour
 */
void RotaryDial::setColour(PicoLed::Color colour){
	xColour = colour;
}

/***
* Notification of rotation
* @param clockwise - Direction. True if clockwise
* @param pos - Current possition (within 360)
* @param rotEnc - Ref to RotEnc in case multiple being used
*/
void RotaryDial::rotate(bool clockwise, int16_t pos, void * rotEnc){
	if (pos < xLength){
		if (pStrip != NULL){
			pStrip->clear();
			pStrip->setPixelColor(pos, xColour);
			pStrip->show();
		}
	}
}
