/**
 * main.cpp
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 *
 *  Example of using PIR
 *  LED (0) will show activity of the PIR PIN
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#include "PIRMgr.h"
#include "PIRObserver.h"
#include "PIRLed.h"



//PAD Definitions
#define PIR_LED 	0
#define PIR			10



int main() {
	stdio_init_all();

	//3second wait to let serial stabalise for debug messages
	sleep_ms(3000);
	printf("Go\n");


	//Construct the objects
	PIRMgr pir(PIR);
	PIRLed pirled(PIR_LED);

	//Set the listeners
	pir.setObserver(&pirled);



	//Loop constantly
    while (true) {
    	;

    	//Could do some other work here.
    }
}
