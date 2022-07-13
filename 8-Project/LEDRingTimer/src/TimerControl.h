/*
 * TimerControl.h
 *
 * Timer control of the Animation, following PIR Detect
 *
 *  Created on: 6 Jul 2022
 *      Author: jondurrant
 */

#ifndef PROJECT_PROJECTASSIGNMENT_SRC_TIMERCONTROL_H_
#define PROJECT_PROJECTASSIGNMENT_SRC_TIMERCONTROL_H_

#include "AnimationsCtr.h"
#include "PIRObserver.h"


class TimerControl : public PIRObserver{
public:
	/***
	 * Constructor
	 * @param timerSec - seconds to remain on following after the PIR clears
	 * @param aniCtr - Animation Control object
	 */
	TimerControl(uint timerSec, AnimationsCtr *aniCtr);
	virtual ~TimerControl();

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

	//Current alarm, <=0 means no alarm present
	alarm_id_t xAlarm = -1;

	//Observer if we are chaining obserers
	PIRObserver *pObserver = NULL;

	//Animation Control
	AnimationsCtr *pAniCtr = NULL;

	//Time that LED should remain on
	uint xTimeSec=0;
};

#endif /* PROJECT_PROJECTASSIGNMENT_SRC_TIMERCONTROL_H_ */
