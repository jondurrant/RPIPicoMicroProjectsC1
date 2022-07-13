/*
 * main.cpp
 * Drive 12 WB2812B on GP15
 * Use rotary encoder to select number of LED to illuminate from 0 to all
 *
 *  Created on: 20 Jun 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>
#include "RotaryDial.h"
#include "RotEncAgent.h"

#define LEDS_PIN 15
#define LEDS_LENGTH 12

#define ROT_ENC_A 2
#define ROT_ENC_B 4


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

	// Set the  colour
	PicoLed::Color c = PicoLed::RGB(0x00, 0xFF, 0x00);


	// Construct our Rotary Encoder
	RotEncAgent rotEnc(ROT_ENC_A, ROT_ENC_B, LEDS_LENGTH);

	// Construct a Ring object listening to the encoder
	RotaryDial dial(&ledStrip, LEDS_LENGTH, c);
	rotEnc.setObserver(&dial);

	// Forever loop calling poll
	while(true){
		rotEnc.poll();

	}

}
