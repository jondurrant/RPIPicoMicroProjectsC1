/*
 * AnimationsCtr.cpp
 *
 * Animation Control - to switch animation sequence and set colour
 *
 *  Created on: 3 Jul 2022
 *      Author: jondurrant
 */

#include "AnimationsCtr.h"

#include "RingChaser.h"
#include "TriTurn.h"
#include "DialUpDown.h"

/***
 * Constructor
 *
 * @param strip - LED strip
 * @param length - number of LEDs in strip
 * @param colour - colour to start with for animations
 * @param stepMS - speed of animation step in miliseconds
 */
AnimationsCtr::AnimationsCtr(
		PicoLed::PicoLedController *strip,
		uint8_t length,
		PicoLed::Color colour,
		uint16_t stepMS) {
	pStrip = strip;
	xLength = length;
	xColour = colour;
	xStepMS = stepMS;

	setupDemos();

}

/***
 * Destructor
 */
AnimationsCtr::~AnimationsCtr() {
	for (uint8_t i=0; i < xDemoCount; i++){
		delete(pDemos[i]);
	}
}

/***
 * Setup the demo animations
 */
void AnimationsCtr::setupDemos(){

	pDemos[0] =  new RingChaser(
				pStrip,
				xLength,
				xColour,
				xStepMS);

	pDemos[1] =  new TriTurn(
				pStrip,
				xLength,
				xColour,
				xStepMS);


	pDemos[2] =  new DialUpDown(
				pStrip,
				xLength,
				xColour,
				xStepMS);


	xColourPicker.setColour(xColour);
	xColourPicker.setStrip(pStrip, xLength);
	xColourPicker.setStepMS(xStepMS);
}


/***
 * Poll - display animation step if needed
 * Should be called frequently from the main loop
 */
void AnimationsCtr::poll(){
	//When in Demo mode poll the demo, otherwise poll colour picker
	switch(xMode){
	case (AnimationsDemos):{
		pDemos[xDemo]->poll();
		break;
	}
	default:{
		xColourPicker.poll();
		break;
	}
	}
}


/***
 * Notification of rotation
 * @param clockwise - Direction. True if clockwise
 * @param pos - Current position (within 360)
 * @param rotEnc - Ref to RotEnc in case multiple being used
 */
void AnimationsCtr::rotate(bool clockwise, int16_t pos, void * rotEnc){
	// If in demo mode hen switch demo, otherwise change colour
	switch(xMode){
	case (AnimationsDemos):{
		switchDemo(clockwise);
		break;
	}
	default:{
		changeColour(clockwise);
		break;
	}
	}
}

/***
 * Change the colour component (R, G or B).
 * @param inc - true then increase brightness, false decrease
 */
void AnimationsCtr::changeColour(bool inc){
	if (inc){
		xColourPicker.incrementColour(COLOUR_STEP);
	}else {
		xColourPicker.derementColour(COLOUR_STEP);
	}

}


/***
 * Change the demo
 * @param inc - if true then move to next, else previous
 */
void AnimationsCtr::switchDemo(bool inc){
	if (inc){
		xDemo++;
		if (xDemo >=xDemoCount){
			xDemo = 0;
		}
	} else {
		if (xDemo == 0){
			xDemo = xDemoCount - 1;
		} else {
			xDemo--;
		}
	}
	pDemos[xDemo]->reset();
	pDemos[xDemo]->setColour(xColour);
	pDemos[xDemo]->setStepMS(xStepMS);
}

/***
 * Handle a short press of the RotEnc Switch
 * Should move into colour change mode, or through colour change component
 * @param gp - Switch GPIO Pad
 */
void AnimationsCtr::handleShortPress(uint8_t gp){
	//In Demo mode then move into colour change mode.
	//In colour change mode move through R, G and B steps
	switch(xMode){
	case AnimationsDemos:{
		xMode = AnimationsSetRed;
		xColourPicker.setColourToPick(PickRed);
		break;
	}
	case AnimationsSetRed:{
		xMode = AnimationsSetGreen;
		xColourPicker.setColourToPick(PickGreen);
		break;
	}
	case AnimationsSetGreen:{
		xMode = AnimationsSetBlue;
		xColourPicker.setColourToPick(PickBlue);
		break;
	}
	case AnimationsSetBlue:{
		xMode = AnimationsDemos;
		xColour = xColourPicker.getColour();
		pDemos[xDemo]->reset();
		pDemos[xDemo]->setColour(xColour);
		break;
	}
	}
}

/***
 * Handle a short press from the switch
 * @param gp - GPIO number of the switch
 */
void AnimationsCtr::handleLongPress(uint8_t gp){
	//Handle as a shortpress
	handleShortPress(gp);
}

