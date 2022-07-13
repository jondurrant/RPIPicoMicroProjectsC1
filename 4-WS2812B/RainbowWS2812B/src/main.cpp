/*
 * main.cpp
 * Drive 12 WB2812B on GP15 through rainbow sequence of colours
 *
 *  Created on: 29 Aug 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>

#define LEDS_PIN 15
#define LEDS_LENGTH 12

//Rainbow sequence as Red, Green, Blue tuples
uint8_t rainbow[][3]= {
	{0x94, 0x00, 0xD3},
	{0x4B, 0x00, 0x82},
	{0x00, 0x00, 0xFF},
	{0x00, 0xFF, 0x00},
	{0xFF, 0xFF, 0x00},
	{0xFF, 0x7F, 0x00},
	{0xFF, 0x00, 0x00}
};

int main(){

    // Initialize LED strip
	auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PIN, LEDS_LENGTH, PicoLed::FORMAT_GRB);

	// Keep brightness low as using 3.3v
	ledStrip.setBrightness(64);


	const int count = 8;

	while(true){
		for (int i=0; i < count; i++){
			//Fill strip with colour
			ledStrip.fill( PicoLed::RGB(rainbow[i][0], rainbow[i][1], rainbow[i][2]) );
			ledStrip.show();
			sleep_ms(500);
		}
	}

}
