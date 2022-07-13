/*
 * TimerLED.h
 *
 * An LED that will illuminate on a PIR Detect and
 * remain on for a number of seconds after the clear is received
 *
 *  Created on: 2 Jul 2022
 *      Author: jondurrant
 */

#ifndef PIR_PIRLED_SRC_TIMERLED_H_
#define PIR_PIRLED_SRC_TIMERLED_H_

#include "PIRObserver.h"
#include <stdio.h>

class TimerLED : public PIRObserver{
public:
	/***
	 * Constructor
	 * @param ledPad - PAD that the LED is connected too
	 * @param timeSec - seconds to remain illuminated after clear
	 */
	TimerLED(uint8_t ledPad, uint16_t timeSec);

	/***
	 * Destructor
	 */
	virtual ~TimerLED();

	/***
	 * Handle PIR Event
	 * @param gp - GPIO number of the PIR
	 */
	virtual void handlePIRDetect(uint8_t gp);

	/***
	 * Handle PIR Event
	 * @param gp - GPIO number of the PIR
	 */
	virtual void handlePIRClear(uint8_t gp);

	/***
	 * Allow chaining of PIR Observers by setting one
	 * @param obs - Observer
	 */
	void setObserver(PIRObserver *obs);

private:
	/***
	 * Call back function for the alarm
	 * @param id - alarm id
	 * @param user_data - will be this object
	 * @return zero on success
	 */
	static int64_t alarmCallback(alarm_id_t id, void *user_data);

	/***
	 * handle an alarm callback
	 * @param id of the alarm
	 */
	void handleAlarm(alarm_id_t id);

	// LED Pad
	uint8_t xLEDPad = 0;

	//Time to remain illuminated
	uint16_t  xTimeSec = 0;

	//Current alarm, <=0 means no alarm present
	alarm_id_t xAlarm = -1;

	//Observer if we are chaining obserers
	PIRObserver *pObserver = NULL;

};

#endif /* PIR_PIRLED_SRC_TIMERLED_H_ */
