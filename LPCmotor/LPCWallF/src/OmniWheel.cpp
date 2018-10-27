/*
 * OmniWheel.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#include <OmniWheel.h>

OmniWheel::OmniWheel(uint8_t portPin1, uint8_t pinPin1, uint8_t portPin2, uint8_t pinPin2,
		uint8_t portint, uint8_t pinint, uint8_t index):
		pin1(portPin1, pinPin1, DigitalIoPin::output, true),
		pin2(portPin2, pinPin2, DigitalIoPin::output, true),
		intpin(portint, pinint, DigitalIoPin::input, false)
{
	mIsClockwise = true;
	pulse = 1000;
	/* Initialize PININT driver */
	Chip_PININT_Init(LPC_GPIO_PIN_INT);
	/* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PININT);

	/* Reset the PININT block */
	Chip_SYSCTL_PeriphReset(RESET_PININT);
	/* Set pin back to GPIO (on some boards may have been changed to something else by Board_Init()) */
	Chip_IOCON_PinMuxSet(LPC_IOCON, portint, pinint, (IOCON_DIGMODE_EN | IOCON_MODE_INACT) );

	/* Configure GPIO pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, portint, pinint);

	/* Configure interrupt channel for the GPIO pin in INMUX block */
	Chip_INMUX_PinIntSel(index, portint, pinint);

	/* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(index));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(index));
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(index));
	NVIC_ClearPendingIRQ(PIN_INT3_IRQn);	//Ymax
	NVIC_EnableIRQ(PIN_INT3_IRQn);
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

