/*
 * HCSerial.h
 *
 *  Created on: Oct 26, 2018
 *      Author: Usin
 */

#ifndef HCSERIAL_H_
#define HCSERIAL_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

class HCSerial {
public:
	HCSerial();
	virtual ~HCSerial();
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
#endif /* HCSERIAL_H_ */
