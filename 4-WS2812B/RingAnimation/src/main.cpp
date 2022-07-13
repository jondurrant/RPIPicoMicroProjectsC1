/*
 * main.cpp
 * Drive 12 WB2812B on GP15
 * Produce a chaser pattern
 *
 *  Created on: 15 Jun 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>
#include "RingChaser.h"

#define LEDS_PIN 15
#define LEDS_LENGTH 12




int main(){

	stdio_init_all();

    // Initialize LED strip
	auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PIN, LEDS_LENGTH, PicoLed::FORMAT_GRB);

	//Keep brightness down as we are running at 3.3v
	ledStrip.setBrightness(64);

	// Initialise the LED to all off
	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0x00 ));
	ledStrip.show();
	sleep_ms(2000);

	// Set the chaser colour
	PicoLed::Color c = PicoLed::RGB(148,0, 211);

	//Create a ring object
	RingChaser ring(
			&ledStrip,
			LEDS_LENGTH,
			c,
			100);


	// Forever loop calling poll
	while(true){
		ring.poll();
	}

}
