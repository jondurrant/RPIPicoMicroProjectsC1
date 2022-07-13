/*
 * LED.cpp
 *
 * Simple LED drive class. Drives LED brightness using PWM
 *
 *  Created on: 9 Jun 2022
 *      Author: jondurrant
 */

#include "LED.h"
#include "hardware/pwm.h"

/***
 * Setup LED on the GPIO pad
 * @param gp - GPIO pad number
 */
LED::LED(uint8_t gp) {
	setGP(gp);
}

/***
 * Construct without initialising GPIO

 */
LED::LED() {
	//NOP
}

LED::~LED() {
	// NOP
}

/***
 * Set the GPIO Pad and initialised it
 * @param gp - GPIO pad number
 */
void LED::setGP(uint8_t gp){
	xGP = gp;

	gpio_init(gp);

	//Setup up PWM to fade LED
	gpio_set_function(gp, GPIO_FUNC_PWM);
	pwm_set_gpio_level(gp, 0);
	uint slice_num = pwm_gpio_to_slice_num(gp);
	pwm_set_enabled(slice_num, true);
}

/***
 * Set brightness
 * @param b - brightness 0 to 0xff
 */
void LED::setBrightness(uint8_t b){
	uint16_t duty = b * b;
	pwm_set_gpio_level(xGP, duty);
}
