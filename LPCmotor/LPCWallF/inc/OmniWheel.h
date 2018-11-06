/*
 * OmniWheel.h
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#ifndef OMNIWHEEL_H_
#define OMNIWHEEL_H_
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif


#include "DigitalIoPin.h"
#include "stdint.h"

class OmniWheel {
public:
	OmniWheel(int portPin1, int pinPin1, int portPin2, int pinPin2, int portint, int pinint, int index);
	void rotate(bool isClockwise, uint32_t pulse);
	void stop();

	bool getDirection();

	virtual ~OmniWheel();

private:
	DigitalIoPin pin1;
	DigitalIoPin pin2;
	bool mIsClockwise;
	uint32_t pulse;
};

#endif /* OMNIWHEEL_H_ */
