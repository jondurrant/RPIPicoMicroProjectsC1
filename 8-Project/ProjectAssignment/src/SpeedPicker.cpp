/*
 * SpeedPicker.cpp
 *
 *  Created on: 5 Jul 2022
 *      Author: jondurrant
 */

#include "SpeedPicker.h"

/***
 * Default constructor
 * SetStrip must be called after this
 */
SpeedPicker::SpeedPicker() : RingAnimation()  {
	// NOP

}

/***
 * Destructor
 */
SpeedPicker::~SpeedPicker() {
	// NOP
}

/***
 * Construct the object
 * @param strip - PicoLed strip object
 * @param length - number of RGB LED in strip
 * @param colour - colour to use for the animation
 * @param stepMS - time in milliseconds between each step of animation
 */
SpeedPicker::SpeedPicker(
	PicoLed::PicoLedController *strip,
	uint8_t length,
	PicoLed::Color colour,
	uint16_t stepMS):
	RingAnimation(strip, length, colour, stepMS){
	//NOP
}


/***
 * Perform step of animation
 */
void SpeedPicker::step(){
	//If step has reached end restart
	if (xStep >= xLength){
		xStep = 0;
	}

	//Only animate if we have a strip
	if (pStrip != NULL){
		pStrip->clear();

		pStrip->setPixelColor(xStep, xColour);

		uint8_t third = ((xLength /3) + xStep) % xLength;
		pStrip->setPixelColor(third, xColour);

		third = (((xLength /3) *2) + xStep) % xLength;
		pStrip->setPixelColor(third, xColour);


		//Animate the first quarter to blink
		PicoLed::Color c = PicoLed::RGB(0,0,0xFF);
		if ((xStep % 2) == 0){
			c = PicoLed::RGB(0,0,0);
		}
		for (uint8_t i=0; i < (xLength/4); i++){
			pStrip->setPixelColor(i, c);
		}

		pStrip->show();
	}
	xStep++;
}

/***
 * Reset animation to start position
 */
void SpeedPicker::reset(){
	RingAnimation::reset();
	xStep = 0;
}

/***
 * Get Current speed
 * @return - step speed in milliseconds
 */
uint16_t SpeedPicker::getStepMS(){
	return xStepMS;
}

/***
 * Increment speed by delta
 * @param delta
 */
void SpeedPicker::incrementSpeed(uint16_t delta){
	if (xStepMS > delta){
		xStepMS = xStepMS - delta;
	}
}

/***
 * Decrement speed by delta
 * @param delta
 */
void SpeedPicker::derementSpeed(uint16_t delta){
	if (xStepMS < (0xFFFF - delta)){
		xStepMS += delta;
	}
}

