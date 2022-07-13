/*
 * main.cpp
 * Drive 12 WB2812B on GP15, RotEnc on GP2,3 and SW on 3
 * Display one of three animations, use RotEnc to move between
 * Use switch to move into colour selection via RotEnc
 *
 *  Created on: 15 Jun 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>

#include "AnimationsCtr.h"
#include "RotEncAgent.h"
#include "SwitchMgr.h"
#include "PIRMgr.h"
#include "PIRLed.h"
#include "TimerControl.h"

#define LEDS_PAD 15
#define LEDS_LENGTH 12
#define STEPMS 100

#define RotEncA  2
#define RotEncB  4
#define RotEnvSw 3

//PAD Definitions
#define PIR_LED 	0
#define PIR			10

//Active Time
#define ACTIVE_SEC	10



int main(){

	stdio_init_all();

    // Initialize LED strip
	auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PAD, LEDS_LENGTH, PicoLed::FORMAT_GRB);

	//Keep brightness down as we are running at 3.3v
	ledStrip.setBrightness(64);

	// Initialise the LED to all off
	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0x00 ));
	ledStrip.show();
	sleep_ms(2000);

	// Set the chaser colour
	PicoLed::Color c = PicoLed::RGB(0xFF, 0xFF, 0xFF);

	//Controller for the animations
	AnimationsCtr control(&ledStrip, LEDS_LENGTH, c, STEPMS);

	//Rotary Encoder
	RotEncAgent rotEnc(RotEncA, RotEncB, LEDS_LENGTH);
	rotEnc.setObserver(&control);

	//Switch on Rotary Encoder
	SwitchMgr switchMgr(RotEnvSw);
	switchMgr.setObserver(&control);

	//Setup PIR
	PIRMgr pir(PIR);
	PIRLed pirled(PIR_LED);
	TimerControl pirTimer(ACTIVE_SEC, &control);
	pir.setObserver(&pirTimer);
	pirTimer.setObserver(&pirled);

	//Poll loop
	while(true){
		control.poll();
		rotEnc.poll();
	}

}
