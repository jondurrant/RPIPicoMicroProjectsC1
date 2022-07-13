/*
 * ColourPicker.cpp
 *
 * Special animation to select a new colour
 * Moves through setting red, green and blue steps
 *
 *  Created on: 3 Jul 2022
 *      Author: jondurrant
 */

#include "ColourPicker.h"

/***
 * Default constructor
 * Should use setStrip, setColour and setStepsMS after construction
 */
ColourPicker::ColourPicker() : RingAnimation() {
	// NOP

}

/***
 * Constructor
 * @param strip - LED Strip
 * @param length - Number of LEDs in the strip
 * @param colour - colour to start with
 * @param stepMS - Animation speed of a step
 */
ColourPicker::ColourPicker(
	PicoLed::PicoLedController *strip,
	uint8_t length,
	PicoLed::Color colour,
	uint16_t stepMS):
	RingAnimation(strip, length, colour, stepMS){
	//NOP
}

/***
 * Destructor
 */
ColourPicker::~ColourPicker(){
	//NOP
}

/***
 * Reset animation to start position
 */
void ColourPicker::reset(){
	RingAnimation::reset();
}


/***
 * Perform step of animation
 */
void ColourPicker::step(){
	PicoLed::Color modeColour = PicoLed::RGB(0xFF, 0x00, 0x00);

	PicoLed::Color brightness = PicoLed::RGB(0x00, 0x00, 0x00);


	switch(xPick){
	case PickRed:{
		modeColour = PicoLed::RGB(0xFF, 0x00, 0x00);
		brightness = PicoLed::RGB(xColour.red, 0x00, 0x00);
		break;
	}
	case PickGreen:{
		modeColour = PicoLed::RGB(0x00, 0xFF, 0x00 );
		brightness = PicoLed::RGB(0x00, xColour.green, 0x00);
		break;
	}
	case PickBlue:{
		modeColour = PicoLed::RGB(0x00, 0x00, 0xFF );
		brightness = PicoLed::RGB(0x00, 0x00, xColour.blue);
		break;
	}
	}

	uint8_t quart = xLength /4;
	uint8_t half = xLength /2;

	for (uint8_t i=0 ; i < quart; i++){
		pStrip->setPixelColor(i, modeColour);
	}

	for (uint8_t i=quart; i < half; i++){
		pStrip->setPixelColor(i, brightness);
	}

	for (uint8_t i=half; i < xLength; i++){
		pStrip->setPixelColor(i, xColour);
	}

	pStrip->show();
}

/***
 * Set which colour we are picking
 * @param p - PickRed, PickGreen, PickBlue
 */
void ColourPicker::setColourToPick(ColourToPick p){
	xPick = p;
}


/***
 * Get current colour, this may have been updated by the animation
 * @return
 */
PicoLed::Color ColourPicker::getColour(){
	return xColour;
}

/***
 * Increment current component (RGB) of colour by the delta if possible
 * @param delta
 */
void ColourPicker::incrementColour(uint8_t delta){
	switch(xPick){
	case PickRed:{
		int i = (int) xColour.red + delta;
		if ( i <= 255){
			xColour = PicoLed::RGB(
				i,
				xColour.green,
				xColour.blue);
		}
		break;
	}
	case PickGreen:{
		int i = (int) xColour.green + delta;
		if ( i <= 255){
			xColour = PicoLed::RGB(
				xColour.red ,
				i,
				xColour.blue);
		}
		break;
	}
	case PickBlue:{
		int i = (int) xColour.blue + delta;
		if ( i <= 255){
		xColour = PicoLed::RGB(
				xColour.red ,
				xColour.green,
				i);
		break;
		}
	}
	}
}

/***
 * Decrement current component (RGB) of colour by the delta if possible
 * @param delta
 */
void ColourPicker::derementColour(uint8_t delta){
	switch(xPick){
	case PickRed:{
		int i = (int) xColour.red - delta;
		if ( i >= 0 ){
			xColour = PicoLed::RGB(
				i,
				xColour.green,
				xColour.blue);
		}
		break;
	}
	case PickGreen:{
		int i = (int) xColour.green - delta;
		if ( i >= 0){
			xColour = PicoLed::RGB(
				xColour.red ,
				i,
				xColour.blue);
		}
		break;
	}
	case PickBlue:{
		int i = (int) xColour.blue - delta;
		if ( i >= 0){
		xColour = PicoLed::RGB(
				xColour.red ,
				xColour.green,
				i);
		break;
		}
	}
	}
}
