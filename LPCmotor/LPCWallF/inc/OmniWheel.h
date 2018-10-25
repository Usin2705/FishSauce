/*
 * OmniWheel.h
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#ifndef OMNIWHEEL_H_
#define OMNIWHEEL_H_
#include "DigitalIoPin.h"

class OmniWheel {
public:
	OmniWheel(int portPin1, int pinPin1, int portPin2, int pinPin2);
	void rotate(bool isClockwise);
	void stop();

	bool getDirection();

	virtual ~OmniWheel();

private:
	DigitalIoPin pin1;
	DigitalIoPin pin2;
	bool mIsClockwise;
};

#endif /* OMNIWHEEL_H_ */
