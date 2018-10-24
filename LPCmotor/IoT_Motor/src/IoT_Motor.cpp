/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif
#include <cr_section_macros.h>
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <mutex>
#include "semphr.h"
#include "queue.h"
// TODO: insert other include files here
#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_
class DigitalIoPin {
public:
	enum pinMode {
		output,
		input,
		pullup,
		pulldown
	};
	DigitalIoPin(int port, int pin, pinMode mode, bool invert = false);
	virtual ~DigitalIoPin();
	virtual bool read();
	void write(bool value);
private:
	int port;
	int pin;
};
#endif
DigitalIoPin::DigitalIoPin(int port_, int pin_, pinMode mode, bool invert) : port(port_), pin(pin_) {
	if(mode == output) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, IOCON_MODE_INACT | IOCON_DIGMODE_EN);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, port, pin);
	}
	else {
		uint32_t pm = IOCON_DIGMODE_EN;
		if(invert) pm |= IOCON_INV_EN;
		if(mode == pullup) {
			pm |= IOCON_MODE_PULLUP;
		}
		else if(mode == pulldown) {
			pm |= IOCON_MODE_PULLDOWN;
		}
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, pm);
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
	}
}
DigitalIoPin::~DigitalIoPin() {
	// TODO Auto-generated destructor stub
}
bool DigitalIoPin::read() {
	return Chip_GPIO_GetPinState(LPC_GPIO, port, pin);
}
void DigitalIoPin::write(bool value) {
	return Chip_GPIO_SetPinState(LPC_GPIO, port, pin, value);
}

// TODO: insert other definitions and declarations here
/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

/* available pins
DigitalIoPin pin5(1,6,DigitalIoPin::output,true);//2.5
DigitalIoPin pin6(0,8,DigitalIoPin::output,true);//2.5
DigitalIoPin pin11(0,10,DigitalIoPin::output,true);//2.5
DigitalIoPin pin12(1,3,DigitalIoPin::output,true);//2.5
DigitalIoPin pin13(0,0,DigitalIoPin::output,true);//2.5
DigitalIoPin pin14(0,24,DigitalIoPin::output,true);//0
DigitalIoPin pin15(1,0,DigitalIoPin::output,true);//2.5
DigitalIoPin pin16(0,27,DigitalIoPin::output,true);//0
DigitalIoPin pin17(0,28,DigitalIoPin::output,true);//2.5
DigitalIoPin pin18(0,12,DigitalIoPin::output,true);//0
DigitalIoPin pin19(0,14,DigitalIoPin::output,true);//2.5
DigitalIoPin pin20(0,23,DigitalIoPin::output,true);//3.2
DigitalIoPin pin21(0,22,DigitalIoPin::output,true);//3.2
 */
//void SCT_Init(void)
//{
//	Chip_SCT_Init(LPC_SCTLARGE0);
//	LPC_SCTLARGE0->CONFIG |= (1 << 17); // two 16-bit timers, auto limit
//	LPC_SCTLARGE0->CONFIG |= (1 << 18); // two 16-bit timers, auto limit
//	LPC_SCTLARGE0->CTRL_L |= (72-1) << 5; // set prescaler, SCTimer/PWM clock = 1 MHz
//	LPC_SCTLARGE0->CTRL_H |= (72-1) << 5; // set prescaler, SCTimer/PWM clock = 1 MHz
//
//	LPC_SCTLARGE0->MATCHREL[0].L = 1000-1; // set the max frequency to 1kHz for the SCT1
//	LPC_SCTLARGE0->MATCHREL[1].L = 500; //
//	LPC_SCTLARGE0->MATCHREL[0].H = 1000-1; // set the max frequency to 1kHz for the SCT2
//	LPC_SCTLARGE0->MATCHREL[3].H = 500; //
//
//	LPC_SCTLARGE0->EVENT[0].STATE = 0xFFFFFFFF; // event 0 happens in all states
//	LPC_SCTLARGE0->EVENT[0].CTRL = (1 << 12); // match 0 condition only
//	LPC_SCTLARGE0->EVENT[1].STATE = 0xFFFFFFFF; // event 1 happens in all states
//	LPC_SCTLARGE0->EVENT[1].CTRL = (1 << 0) | (1 << 12); // match 1 condition only
//	LPC_SCTLARGE0->EVENT[2].STATE = 0xFFFFFFFF; // event 0 happens in all states
//	LPC_SCTLARGE0->EVENT[2].CTRL = (1 << 12) | (1 << 4); // match 1 condition only
//	LPC_SCTLARGE0->EVENT[3].STATE = 0xFFFFFFFF; // event 1 happens in all states
//	LPC_SCTLARGE0->EVENT[3].CTRL = (3 << 0) | (1 << 12) | (1 << 4); // match 3 conditions
//	LPC_SCTLARGE0->OUT[0].SET = (1 << 0); // event 0 will set SCTx_OUT0
//	LPC_SCTLARGE0->OUT[0].CLR = (1 << 1); // event 1 will clear SCTx_OUT0
//
//	LPC_SCTLARGE0->OUT[1].SET = (1 << 0); // event 0 will set SCTx_OUT0
//	LPC_SCTLARGE0->OUT[1].CLR = (1 << 3); // event 1 will clear SCTx_OUT0
//
//	LPC_SCTLARGE0->CTRL_L &= ~(1 << 2); // unhalt it by clearing bit 2 of CTRL reg
//	LPC_SCTLARGE0->CTRL_H &= ~(1 << 2); // unhalt it by clearing bit 2 of CTRL reg
//
//
//	Chip_SWM_MovablePortPinAssign(SWM_SCT0_OUT0_O,0,8);
//	Chip_SWM_MovablePortPinAssign(SWM_SCT0_OUT0_O,1,6);
//
//}
//void PWM_set(int val) {
//	LPC_SCTLARGE0->MATCHREL[3].L = val;
//	LPC_SCTLARGE0->MATCHREL[1].L = val;
//}

static void vTask1(void *pvParameters) {

	//move left and right
	DigitalIoPin west1(1,10,DigitalIoPin::output,true);
	DigitalIoPin west2(1,9,DigitalIoPin::output,true);
	DigitalIoPin east3(0,29,DigitalIoPin::output,true);
	DigitalIoPin east4(0,9,DigitalIoPin::output,true);

	//move up and down
	DigitalIoPin north1(0,7,DigitalIoPin::output,true);
	DigitalIoPin north2(0,6,DigitalIoPin::output,true);
	DigitalIoPin south3(0,5,DigitalIoPin::output,true);
	DigitalIoPin south4(1,8,DigitalIoPin::output,true);
	int c = 0;
	char m[80] = {0};
	int i = 0;
	int count = 0;
	char st[80] = {0};
	while(1){
		c=Board_UARTGetChar();
		if(i < 80 && c != EOF){
			m[i] = c;
			i++;
			Board_UARTPutChar(c);
			if (c == '\r' || c == '\n') {
				m[i] = '\0';
				i = 0;
				Board_UARTPutSTR("\r\n");
				sscanf(m,"%s %d",st,&count);
				if(m[0]=='l'&&m[1]=='e'&&m[2]=='f'&&m[3]=='t'){
					west1.write(true);
					east3.write(true);
					west2.write(false);
					east4.write(false);
					vTaskDelay(count);
					west1.write(false);
					east3.write(false);
					west2.write(false);
					east4.write(false);
				}
				if(m[0]=='r'&&m[1]=='i'&&m[2]=='g'&&m[3]=='h'&&m[4]=='t'){
					west1.write(false);
					east3.write(false);
					west2.write(true);
					east4.write(true);
					vTaskDelay(count);
					west1.write(false);
					east3.write(false);
					west2.write(false);
					east4.write(false);
				}
				if(m[0]=='u'&&m[1]=='p'){
					north1.write(false);
					south3.write(false);
					north2.write(true);
					south4.write(true);
					vTaskDelay(count);
					north1.write(false);
					south3.write(false);
					north2.write(false);
					south4.write(false);
				}
				if(m[0]=='d'&&m[1]=='o'&&m[2]=='w'&&m[3]=='n'){
					north1.write(true);
					south3.write(true);
					north2.write(false);
					south4.write(false);
					vTaskDelay(count);
					north1.write(false);
					south3.write(false);
					north2.write(false);
					south4.write(false);
				}
				if(m[0]=='c'&&m[1]=='l'&&m[2]=='o'&&m[3]=='c'&&m[4]=='k'&&m[5]=='w'&&m[6]=='i'&&m[7]=='s'&&m[8]=='e'){
					west1.write(false);
					east3.write(true);
					north1.write(false);
					south3.write(true);
					west2.write(true);
					east4.write(false);
					north2.write(true);
					south4.write(false);
					vTaskDelay(count);
					west1.write(false);
					east3.write(false);
					north1.write(false);
					south3.write(false);
					west2.write(false);
					east4.write(false);
					north2.write(false);
					south4.write(false);
				}
				if(m[0]=='c'&&m[1]=='o'&&m[2]=='u'&&m[3]=='n'&&m[4]=='t'&&m[5]=='e'&&m[6]=='r'
						&&m[7]=='c'&&m[8]=='l'&&m[9]=='o'&&m[10]=='c'&&m[11]=='k'&&m[12]=='w'&&m[13]=='i'&&m[14]=='s'&&m[15]=='e'){
					west1.write(true);
					east3.write(false);
					north1.write(true);
					south3.write(false);
					west2.write(false);
					east4.write(true);
					north2.write(false);
					south4.write(true);
					vTaskDelay(count);
					west1.write(false);
					east3.write(false);
					north1.write(false);
					south3.write(false);
					west2.write(false);
					east4.write(false);
					north2.write(false);
					south4.write(false);
				}
			}
		}
		vTaskDelay(1);
	}
}
extern "C" {

void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}

int main(void) {
	prvSetupHardware();
//	SCT_Init();
	/* LED1 toggle thread */
	xTaskCreate(vTask1, "vTask1",
			configMINIMAL_STACK_SIZE*10, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
