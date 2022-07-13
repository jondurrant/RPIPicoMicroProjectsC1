/*
 * RGBLED.cpp
 *
 *  Created on: 10 Jun 2022
 *      Author: jondurrant
 */

#include "RGBLED.h"

RGBLED::RGBLED(uint8_t rGP, uint8_t gGP, uint8_t bGP){
	xRed.setGP(rGP);
	xGreen.setGP(gGP);
	xBlue.setGP(bGP);
}

RGBLED::~RGBLED() {
	//  NOP
}

/***
 * Set colour based of LED,
 * @param red - 0 to 0xff
 * @param green - 0 to 0xff
 * @param blue - 0 to 0xff
 */
void RGBLED::setColour(uint8_t red, uint8_t green, uint8_t blue){
	xRed.setBrightness(red);
	xGreen.setBrightness(green);
	xBlue.setBrightness(blue);
}


/***
 *set colour of LED
 * @param rgb - array of three bytes in order Red, Green, Blue
 */
void RGBLED::setColour(uint8_t rgb[]){
	setColour(rgb[0], rgb[1], rgb[2]);

}
