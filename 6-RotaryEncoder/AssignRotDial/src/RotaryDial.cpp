/*
 * RingRotate.cpp
 *
 *  Created on: 20 Jun 2022
 *      Author: jondurrant
 */

#include "RotaryDial.h"

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

	if (clockwise){
		if (xLevel <= xLength -1){
			xLevel ++;
		}
	} else {
		if (xLevel > 0){
			xLevel --;
		}

	}

	if (pStrip != NULL){
		pStrip->clear();

		for (uint8_t i =0; i < xLevel; i++){
			pStrip->setPixelColor(i, xColour);
		}

		pStrip->show();
	}

}
