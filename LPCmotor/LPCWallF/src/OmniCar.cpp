/*
 * OmniCar.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#include <OmniCar.h>

OmniCar::OmniCar(){
	SystemCoreClockUpdate();
	Board_Init();
	/* Initialize PININT driver */
	Chip_PININT_Init(LPC_GPIO_PIN_INT);
	/* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PININT);
	/* Reset the PININT block */
	Chip_SYSCTL_PeriphReset(RESET_PININT);
	north = new OmniWheel(1, 10, 1, 9, 0, 0, 0);
	south = new OmniWheel(0, 29, 0, 9, 0, 23, 1);
	east = new OmniWheel(0, 7, 0, 6, 1, 0, 2);
	west = new OmniWheel(0, 5, 1, 8, 0, 22, 3);
}

OmniCar::~OmniCar() {
	delete north;
	delete south;
	delete east;
	delete west;
}

void OmniCar::move(DIRECTION direction) {
	switch (direction) {
	case UP:
		east->rotate(!ISCLOCKWISE);
		west->rotate(ISCLOCKWISE);
		break;
	case DOWN:
		east->rotate(ISCLOCKWISE);
		west->rotate(!ISCLOCKWISE);
		break;
	case LEFT:
		north->rotate(!ISCLOCKWISE);
		south->rotate(ISCLOCKWISE);
		break;
	case RIGHT:
		north->rotate(ISCLOCKWISE);
		south->rotate(!ISCLOCKWISE);
		break;
	default:
		break;
	}
}

void OmniCar::indimove(WHEEL wheel, bool dir) {
	switch(wheel) {
	case NORTH:
		this->north->setEnable();
		this->north->rotate(dir);
		break;
	case SOUTH:
		this->south->setEnable();
		this->south->rotate(dir);
		break;
	case EAST:
		this->east->setEnable();
		this->east->rotate(dir);
		break;
	case WEST:
		this->west->setEnable();
		this->west->rotate(dir);
		break;
	}
}

void OmniCar::turn(DIRECTION direction) {
	switch (direction) {
	case LEFT:
		east->rotate(ISCLOCKWISE);
		west->rotate(ISCLOCKWISE);
		north->rotate(ISCLOCKWISE);
		south->rotate(ISCLOCKWISE);
		break;
	case RIGHT:
		east->rotate(!ISCLOCKWISE);
		west->rotate(!ISCLOCKWISE);
		north->rotate(!ISCLOCKWISE);
		south->rotate(!ISCLOCKWISE);
		break;
	default:
		break;
	}
}

void OmniCar::stopWheel(WHEEL wheel) {
	switch(wheel) {
	case NORTH:
		this->north->stop();
		break;
	case SOUTH:
		this->south->stop();
		break;
	case EAST:
		this->east->stop();
		break;
	case WEST:
		this->west->stop();
		break;
	}
}

void OmniCar::setWheelEnable(WHEEL wheel) {
	switch(wheel) {
	case NORTH:
		this->north->setEnable();
		break;
	case SOUTH:
		this->south->setEnable();
		break;
	case EAST:
		this->east->setEnable();
		break;
	case WEST:
		this->west->setEnable();
		break;
	}
}
