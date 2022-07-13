/**
 * main.cpp
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 *
 *  Example of using PIR with a timer.
 *  One LED (0) will show activity of the PIR PIN
 *  Second LED (1) will activate and remain active for 10 seconds after the PIR has cleared
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#include "PIRMgr.h"
#include "PIRObserver.h"
#include "PIRLed.h"
#include "TimerLED.h"


//PAD Definitions
#define PIR_LED 	0
#define ACTIVE_LED	1
#define PIR			10

//Active Time
#define ACTIVE_SEC	10


int main() {
	stdio_init_all();

	//3second wait to let serial stabalise for debug messages
	sleep_ms(3000);
	printf("Go\n");


	//Construct the objects
	PIRMgr pir(PIR);
	PIRLed pirled(PIR_LED);
	TimerLED timerled(ACTIVE_LED, ACTIVE_SEC);

	//Set the listeners
	timerled.setObserver(&pirled);
	pir.setObserver(&timerled);


	//Loop constantly
    while (true) {
    	;

    	//Could do some other work here.
    }
}
