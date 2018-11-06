/*
 * OmniWheel.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#include <OmniWheel.h>

OmniWheel::OmniWheel(int portPin1, int pinPin1, int portPin2, int pinPin2, int portint, int pinint, int index):
pin1(portPin1, pinPin1, DigitalIoPin::output, true),
pin2(portPin2, pinPin2, DigitalIoPin::output, true)
{
	mIsClockwise = true;
	pulse = 0;
	/* Set pin back to GPIO (on some boards may have been changed to something
		   else by Board_Init()) */
	Chip_IOCON_PinMuxSet(LPC_IOCON, portint, pinint,
			(IOCON_DIGMODE_EN | IOCON_MODE_INACT) );
	/* Configure GPIO pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, portint, pinint);
	/* Configure interrupt channel for the GPIO pin in INMUX block */
	Chip_INMUX_PinIntSel(index, portint, pinint);
	/* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(index));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(index));
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(index));
	switch (index) {
	case 0:
		NVIC_ClearPendingIRQ(PIN_INT0_IRQn);
		NVIC_EnableIRQ(PIN_INT0_IRQn);
		break;
	case 1:
		NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
		NVIC_EnableIRQ(PIN_INT1_IRQn);
		break;
	case 2:
		NVIC_ClearPendingIRQ(PIN_INT2_IRQn);
		NVIC_EnableIRQ(PIN_INT2_IRQn);
		break;
	case 3:
		NVIC_ClearPendingIRQ(PIN_INT3_IRQn);
		NVIC_EnableIRQ(PIN_INT3_IRQn);
		break;
	}
}

/*
 * Rotate the motor clockwise or counter clockwise
 * if motor is rotating clockwise, pin1 must write true
 * then pin2 must write false
 * Also update the direction of the motor, just in case we need it
 * (probably need it in counting the hall signal)
 *
 */
void OmniWheel::rotate(bool isClockwise, uint32_t pulse) {
	mIsClockwise = isClockwise;
	this->pulse = pulse;
	if(this->pulse > 0) {
		pin1.write(isClockwise);
		pin2.write(!isClockwise);
	}
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

