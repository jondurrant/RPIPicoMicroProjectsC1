/*
 * AnimationsCtr.h
 *
 * Animation Control - to switch animation sequence and set colour
 *
 *  Created on: 3 Jul 2022
 *      Author: jondurrant
 */

#ifndef LEDRINGPROJECT_SRC_ANIMATIONSCTR_H_
#define LEDRINGPROJECT_SRC_ANIMATIONSCTR_H_

#include "RotEncObserver.h"
#include <PicoLed.hpp>
#include "RingAnimation.h"
#include "SwitchObserver.h"
#include "ColourPicker.h"

//Colour step to change with each click of the RotEnc
#define COLOUR_STEP 5


//Animation mode - showing demos or selecting colour
enum AnimationsMode {AnimationsDemos, AnimationsSetRed, AnimationsSetGreen, AnimationsSetBlue};

class AnimationsCtr : public RotEncObserver, public SwitchObserver{
public:
	/***
	 * Constructor
	 *
	 * @param strip - LED strip
	 * @param length - number of LEDs in strip
	 * @param colour - colour to start with for animations
	 * @param stepMS - speed of animation step in miliseconds
	 */
	AnimationsCtr(
			PicoLed::PicoLedController *strip,
			uint8_t length,
			PicoLed::Color colour,
			uint16_t stepMS);

	/***
	 * Destructor
	 */
	virtual ~AnimationsCtr();

	/***
	 * Notification of rotation
	 * @param clockwise - Direction. True if clockwise
	 * @param pos - Current position (within 360)
	 * @param rotEnc - Ref to RotEnc in case multiple being used
	 */
	virtual void rotate(bool clockwise, int16_t pos, void * rotEnc);

	/***
	 * Handle a short press of the RotEnc Switch
	 * Should move into colour change mode, or through colour change component
	 * @param gp - Switch GPIO Pad
	 */
	virtual void handleShortPress(uint8_t gp);

	/***
	 * Handle a short press from the switch
	 * @param gp - GPIO number of the switch
	 */
	virtual void handleLongPress(uint8_t gp);


	/***
	 * Poll - display animation step if needed
	 * Should be called frequently from the main loop
	 */
	void poll();

private:
	/***
	 * Setup the demo animations
	 */
	void setupDemos();

	/***
	 * Change the demo
	 * @param inc - if true then move to next, else previous
	 */
	void switchDemo(bool inc);

	/***
	 * Change the colour component (R, G or B).
	 * @param inc - true then increase brightness, false decrease
	 */
	void changeColour(bool inc);

	//Number of demo animations
	const uint8_t xDemoCount = 3;

	//Array of the demos
	RingAnimation * pDemos[3];

	//Current demo index
	uint8_t xDemo = 0;

	//Step speed of the animation
	uint16_t xStepMS = 0;

	//Steip details and current colour
	PicoLed::PicoLedController *pStrip = NULL;
	uint8_t xLength = 0;
	PicoLed::Color xColour = PicoLed::RGB(0xFF, 0xFF, 0xFF);


	// Current mode, showing demos or changing colour
	AnimationsMode xMode = AnimationsDemos;

	//Colour picker object
	ColourPicker xColourPicker;
};

#endif /* LEDRINGPROJECT_SRC_ANIMATIONSCTR_H_ */
