/*
 * TimerLED.cpp
 *
 * An LED that will illuminate on a PIR Detect and
 * remain on for a number of seconds after the clear is received
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#include "TimerLED.h"

/***
 * Constructor
 * @param ledPad - PAD that the LED is connected too
 * @param timeSec - seconds to remain illuminated after clear
 */
TimerLED::TimerLED(uint8_t ledPad, uint16_t timeSec){
	xLEDPad = ledPad;
	xTimeSec = timeSec;

	//Initialise the LED and set it's initial state
	gpio_init(xLEDPad);
	gpio_set_dir(xLEDPad, GPIO_OUT);
	gpio_put(xLEDPad, 0);

}

/***
 * Destructor
 */
TimerLED::~TimerLED() {
	// NOP
}

void TimerLED::setObserver(PIRObserver *obs){
	pObserver = obs;
}


/***
 * Handle PIR Event
 * @param gp - GPIO number of the PIR
 */
void TimerLED::handlePIRDetect(uint8_t gp){
	//Turn on LED
	gpio_put(xLEDPad, 1);

	//If current alarm cancel it
	if (xAlarm > 0){
		cancel_alarm(xAlarm);
	}

	//Notify observers of event
	if (pObserver != NULL){
		pObserver->handlePIRDetect(gp);
	}
}

/***
 * Handle PIR Event
 * @param gp - GPIO number of the PIR
 */
void TimerLED::handlePIRClear(uint8_t gp){

	// If alarm present then cancel it
	if (xAlarm > 0){
		cancel_alarm(xAlarm);
	}

	// Start an alarm for the required number of seconds
	xAlarm = add_alarm_in_ms(xTimeSec*1000,
		TimerLED::alarmCallback,
		this,
		true
		);

	// Chain observer call
	if (pObserver != NULL){
		pObserver->handlePIRClear(gp);
	}
}

/***
 * Call back function for the alarm
 * @param id - alarm id
 * @param user_data - will be this object
 * @return zero on success
 */
int64_t TimerLED::alarmCallback(alarm_id_t id, void *user_data){
	//Pass control to the object function handleAlarm
	TimerLED *t = (TimerLED *) user_data;
	t->handleAlarm(id);
	return 0;
}

/***
 * handle an alarm callback
 * @param id of the alarm
 */
void TimerLED::handleAlarm(alarm_id_t id){

	//If this is the current alarm then turn off the LED
	if (id == xAlarm){
		xAlarm = -1;
		gpio_put(xLEDPad, 0);
	}
}
