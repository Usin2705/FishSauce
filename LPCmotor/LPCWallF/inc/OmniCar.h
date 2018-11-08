/*
 * OmniCar.h
 *
 *  Created on: Oct 25, 2018
 *      Author: Usin
 */

#ifndef OMNICAR_H_
#define OMNICAR_H_
#include "OmniWheel.h"

#define ISCLOCKWISE true

typedef enum {UP,DOWN,LEFT,RIGHT} DIRECTION;
typedef enum {NORTH, SOUTH, EAST, WEST} WHEEL;

class OmniCar {
public:
	OmniCar();
	virtual ~OmniCar();

	void move(DIRECTION direction);
	void indiMove(WHEEL wheel, bool dir);
	void turn(DIRECTION direction);
	void stopWheel(WHEEL wheel);
	void setWheelEnable(WHEEL wheel);

private:
	OmniWheel *north;
	OmniWheel *south;
	OmniWheel *east;
	OmniWheel *west;
};

#endif /* OMNICAR_H_ */
