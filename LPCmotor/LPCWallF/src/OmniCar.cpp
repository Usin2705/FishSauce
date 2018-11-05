/*
 * OmniCar.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#include <OmniCar.h>

OmniCar::OmniCar(){
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

void OmniCar::move(DIRECTION direction, uint32_t pulse) {
	switch (direction) {
	case UP:
		east->rotate(!ISCLOCKWISE, pulse);
		west->rotate(ISCLOCKWISE, pulse);
		break;
	case DOWN:
		east->rotate(ISCLOCKWISE, pulse);
		west->rotate(!ISCLOCKWISE, pulse);
		break;
	case LEFT:
		north->rotate(!ISCLOCKWISE, pulse);
		south->rotate(ISCLOCKWISE, pulse);
		break;
	case RIGHT:
		north->rotate(ISCLOCKWISE, pulse);
		south->rotate(!ISCLOCKWISE, pulse);
		break;
	default:
		break;
	}
}

void OmniCar::turn(DIRECTION direction, uint32_t pulse) {
	switch (direction) {
	case LEFT:
		east->rotate(ISCLOCKWISE, pulse);
		west->rotate(ISCLOCKWISE, pulse);
		north->rotate(ISCLOCKWISE, pulse);
		south->rotate(ISCLOCKWISE, pulse);
		break;
	case RIGHT:
		east->rotate(!ISCLOCKWISE, pulse);
		west->rotate(!ISCLOCKWISE, pulse);
		north->rotate(!ISCLOCKWISE, pulse);
		south->rotate(!ISCLOCKWISE, pulse);
		break;
	default:
		break;
	}
}

void OmniCar::stop() {
	north->stop();
	south->stop();
	east->stop();
	west->stop();
}
