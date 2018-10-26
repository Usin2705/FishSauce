/*
 * RPSerial.h
 *
 *  Created on: Oct 26, 2018
 *      Author: Usin
 */

#ifndef RPSERIAL_H_
#define RPSERIAL_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

class RPSerial {
public:
	RPSerial();
	virtual ~RPSerial();
	int available();
	void begin(int speed = 9600);
	int read();
	int write(const char* buf, int len);
	int print(int val, int format);
	void flush();
private:
	static const int UART_RB_SIZE = 128;
	/* Transmit and receive ring buffers */
	RINGBUFF_T txring;
	RINGBUFF_T rxring;
	uint8_t rxbuff[UART_RB_SIZE];
	uint8_t txbuff[UART_RB_SIZE];


};
#endif /* RPSERIAL_H_ */
