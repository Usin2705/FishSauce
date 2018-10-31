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
	OmniWheel(uint8_t portPin1, uint8_t pinPin1, uint8_t portPin2, uint8_t pinPin2, uint8_t portint, uint8_t pinint, uint8_t index);
	void rotate(bool isClockwise);
	void stop();

	bool getDirection();

	virtual ~OmniWheel();

private:
	DigitalIoPin pin1;
	DigitalIoPin pin2;
	DigitalIoPin intpin;
	bool mIsClockwise;
	uint32_t pulse;
};

#endif /* OMNIWHEEL_H_ */
