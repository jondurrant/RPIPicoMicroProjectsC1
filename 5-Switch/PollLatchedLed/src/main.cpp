/**
 * main.cpp
 *
 *  Created on: 1 Jun 2022
 *      Author: jondurrant
 *
 *  Example of reading a switch using a polling strategy.
 *  Uses momentary switch on GP0 to provide a latched (turn on and turn off)
 *  of the on board LED
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#include "SwitchMgr.h"
#include "LedMgr.h"



int main() {
	stdio_init_all();

	//3second wait to let serial stabalise for debug messages
	sleep_ms(3000);
	printf("Go\n");


	//Construct our two objects, Led Manager and Switch Manager
	LedMgr ledMgr(16);
	SwitchMgr switchMgr(0);

	//Let Led Manager be an observer on Switch Mgr
	switchMgr.setObserver(&ledMgr);


	//Loop constantly calling poll method of Switch Mgr
    while (true) {
    	switchMgr.poll();

    	//Could do some other work here.
    }
}
