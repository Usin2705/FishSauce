/*
 * OmniCar.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#include <OmniCar.h>

OmniCar::OmniCar(){
	north = new OmniWheel(1,10,1,9);
	south = new OmniWheel(0,29,0,9);
	east = new OmniWheel(0,7,0,6);
	west = new OmniWheel(0,5,1,8);
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

void OmniCar::stop() {
	north->stop();
	south->stop();
	east->stop();
	west->stop();
}
