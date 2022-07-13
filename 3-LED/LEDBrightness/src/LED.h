/*
 * LED.h
 *
 *  Created on: 9 Jun 2022
 *      Author: jondurrant
 */

#ifndef LED_LEDBRIGHTNESS_SRC_LED_H_
#define LED_LEDBRIGHTNESS_SRC_LED_H_

#include <stdlib.h>
#include "pico/stdlib.h"

class LED {
public:
	/***
	 * Constructor without initialising LED
	 */
	LED();

	/***
	 * Setup LED on the GPIO pad
	 * @param gp - GPIO pad number
	 */
	LED(uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~LED();

	/***
	 * Set the GPIO Pad and initialised it
	 * @param gp - GPIO pad number
	 */
	void setGP(uint8_t gp);

	/***
	 * Set brightness
	 * @param b - brightness 0 to 0xff
	 */
	void setBrightness(uint8_t b);

private:
	// GPIO Pad number
	uint8_t xGP = 0;

};

#endif /* LED_LEDBRIGHTNESS_SRC_LED_H_ */
