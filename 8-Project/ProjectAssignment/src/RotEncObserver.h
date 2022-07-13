/*
 * RotEnvListener.h
 *
 * Abstract observer for the RotEnc
 *
 *  Created on: 20 June 2022
 *      Author: jondurrant
 */

#ifndef ROTENC_SRC_ROTENCLISTENER_H_
#define ROTENC_SRC_ROTENCLISTENER_H_

#include <stdint.h>

class RotEncObserver {
public:
	/***
	 * Constructor
	 */
	RotEncObserver();

	/***
	 * Destructor
	 */
	virtual ~RotEncObserver();

	/***
	 * Notification of rotation
	 * @param clockwise - Direction. True if clockwise
	 * @param pos - Current position (within 360)
	 * @param rotEnc - Ref to RotEnc in case multiple being used
	 */
	virtual void rotate(bool clockwise, int16_t pos, void * rotEnc);

};

#endif /* ROTENC_SRC_ROTENCLISTENER_H_ */
