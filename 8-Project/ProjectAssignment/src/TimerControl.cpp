/*
 * TimerControl.cpp
 *
 *  Created on: 6 Jul 2022
 *      Author: jondurrant
 */

#include "TimerControl.h"

/***
 * Constructor
 * @param timerSec - seconds to remain on following after the PIR clears
 * @param aniCtr - Animation Control object
 */
TimerControl::TimerControl(uint timerSec, AnimationsCtr *aniCtr) {
	pAniCtr = aniCtr;
	xTimeSec = timerSec;
}

/***
 * Destructor
 */
TimerControl::~TimerControl() {
	// NOP
}

/***
 * Allow chaining of PIR Observers by setting one
 * @param obs - Observer
 */
void TimerControl::setObserver(PIRObserver *obs){
	pObserver = obs;
}


/***
 * Handle PIR Event
 * @param gp - GPIO number of the PIR
 */
void TimerControl::handlePIRDetect(uint8_t gp){
	if (pAniCtr != NULL){
		pAniCtr->switchPower(true);
	}

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
void TimerControl::handlePIRClear(uint8_t gp){

	// If alarm present then cancel it
	if (xAlarm > 0){
		cancel_alarm(xAlarm);
	}

	// Start an alarm for the required number of seconds
	xAlarm = add_alarm_in_ms(xTimeSec*1000,
		TimerControl::alarmCallback,
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
int64_t TimerControl::alarmCallback(alarm_id_t id, void *user_data){
	//Pass control to the object function handleAlarm
	TimerControl *t = (TimerControl *) user_data;
	t->handleAlarm(id);
	return 0;
}

/***
 * handle an alarm callback
 * @param id of the alarm
 */
void TimerControl::handleAlarm(alarm_id_t id){

	//If this is the current alarm then turn off the LED
	if (id == xAlarm){
		xAlarm = -1;
		if (pAniCtr != NULL){
			pAniCtr->switchPower(false);
		}
	}
}
