/*
 * OmniWheel.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#include <OmniWheel.h>

OmniWheel::OmniWheel(int portPin1, int pinPin1, int portPin2, int pinPin2):
	pin1(portPin1, pinPin1, DigitalIoPin::output,true),
	pin2(portPin2, pinPin2, DigitalIoPin::output,true)
{
	mIsClockwise = true;
}

/*
 * Rotate the motor clockwise or counter clockwise
 * if motor is rotating clockwise, pin1 must write true
 * then pin2 must write false
 * Also update the direction of the motor, just in case we need it
 * (probably need it in counting the hall signal)
 *
 */
void OmniWheel::rotate(bool isClockwise) {
	mIsClockwise = isClockwise;
	pin1.write(isClockwise);
	pin2.write(!isClockwise);
}

bool OmniWheel::getDirection() {return mIsClockwise;}

/*
 * Stop the rotation of the wheel by set both pins
 * to false
 */
void OmniWheel::stop() {
	pin1.write(false);
	pin2.write(false);
}

OmniWheel::~OmniWheel() {
	// TODO Auto-generated destructor stub
}

