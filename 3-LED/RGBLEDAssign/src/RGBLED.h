/*
 * RGBLED.h
 *
 * RGB LED Class
 *
 *  Created on: 10 Jun 2022
 *      Author: jondurrant
 */

#ifndef LED_LEDFADER_SRC_RGBLED_H_
#define LED_LEDFADER_SRC_RGBLED_H_

#include "LED.h"
#include "pico/stdlib.h"
#include <stdlib.h>

class RGBLED {
public:
	/***
	 * Constructor. Initialises the GPIO Pads for the LED
	 * @param rGP - Red GPIO Pad
	 * @param gGP - Green GPIO Pad
	 * @param bGP - Blue GPIO Pad
	 */
	RGBLED(uint8_t rGP, uint8_t gGP, uint8_t bGP);
	virtual ~RGBLED();

	/***
	 * Set colour of LED,
	 * @param red - 0 to 0xff
	 * @param green - 0 to 0xff
	 * @param blue - 0 to 0xff
	 */
	void setColour(uint8_t red, uint8_t green, uint8_t blue);


	/***
	 *set colour of LED
	 * @param rgb - array of three bytes in order Red, Green, Blue
	 */
	void setColour(uint8_t rgb[]);

private:
	LED xRed;
	LED xBlue;
	LED xGreen;
};

#endif /* LED_LEDFADER_SRC_RGBLED_H_ */
