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

class OmniCar {
public:
	OmniCar();
	virtual ~OmniCar();

	void move(DIRECTION direction, uint32_t pulse);
	void turn(DIRECTION direction, uint32_t pulse);
	void stop();

private:
	OmniWheel *north;
	OmniWheel *south;
	OmniWheel *east;
	OmniWheel *west;
};

#endif /* OMNICAR_H_ */
