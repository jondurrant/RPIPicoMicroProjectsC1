/*
 * ChaserTail.cpp
 *
 *  Created on: 15 Jun 2022
 *      Author: jondurrant
 */

#include "ChaserTail.h"

ChaserTail::ChaserTail()  : RingAnimation() {
	// NOP

}

/***
 * Construct the object
 * @param strip - PicoLed strip object
 * @param length - number of RGB LED in strip
 * @param colour - colour to use for the animation
 * @param stepMS - time in milliseconds between each step of animation
 */
ChaserTail::ChaserTail(
	PicoLed::PicoLedController *strip,
	uint8_t length,
	PicoLed::Color colour,
	uint16_t stepMS):
	RingAnimation(strip, length, colour, stepMS){
	//NOP
}

ChaserTail::~ChaserTail() {
	// NOP
}

/***
 * Perform step of animation
 */
void ChaserTail::step(){
	//If step has reached end restart
	if (xStep >= xLength){
		xStep = 0;
	}

	//Only animate if we have a strip
	if (pStrip != NULL){
		// Clear and set the head of the chaser
		pStrip->clear();
		pStrip->setPixelColor(xStep, xColour);

		// Calculate the tail start position and length
		uint8_t start = xStep + xLength -1;
		uint8_t tail = xLength /4;
		float factor;
		for (uint8_t i = 0; i < tail; i++){

			//Calculate the colour reduced for this pixel as
			// a percentage of double the tail length
			uint8_t r,g,b;
			factor = (float)(i+1) / (float)(tail*2);
			r = (float) xColour.red * factor;
			g =  (float) xColour.green * factor;
			b = (float) xColour.red * factor;
			PicoLed::Color c = PicoLed::RGB(r, g, b);

			//The first pixel in the tail is the farthest from head.
			//Calculate its position
			uint8_t pixel = (xStep + xLength - tail + i) % xLength;

			//Draw pixel
			pStrip->setPixelColor(pixel, c);
		}
		pStrip->show();
	}
	xStep++;
}


/***
 * Reset animation to start position
 */
void ChaserTail::reset(){
	RingAnimation::reset();
	xStep = 0;
}
