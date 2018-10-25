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
#include "DigitalIoPin.h"
#include "OmniCar.h"
#include <cstring>


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
 	DigitalIoPin northPin1(1,10,DigitalIoPin::output,true);
	DigitalIoPin northPin2(1,9,DigitalIoPin::output,true);
	DigitalIoPin southPin1(0,29,DigitalIoPin::output,true);
	DigitalIoPin southPin2(0,9,DigitalIoPin::output,true);

	DigitalIoPin eastPin1(0,7,DigitalIoPin::output,true);
	DigitalIoPin eastPin2(0,6,DigitalIoPin::output,true);
	DigitalIoPin westPin1(0,5,DigitalIoPin::output,true);
	DigitalIoPin westPin2(1,8,DigitalIoPin::output,true);

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
	OmniCar omniCar;
	int c = 0;
	char cmd[80] = {0};
	int i = 0;
	int count = 0;
	char st[80] = {0};
	while(1){
		c=Board_UARTGetChar();
		if(i < 80 && c != EOF){
			cmd[i] = c;
			i++;
			Board_UARTPutChar(c);
			if (c == '\r' || c == '\n') {
				cmd[i] = '\0';
				i = 0;
				Board_UARTPutSTR("\r\n");
				sscanf(cmd,"%s %d",st,&count);

				if(strstr(cmd, "left ") != NULL){
					omniCar.move(DIRECTION::LEFT);
					vTaskDelay(count);
				}
				if(strstr(cmd, "right ") != NULL){
					omniCar.move(DIRECTION::RIGHT);
					vTaskDelay(count);
				}
				if(strstr(cmd, "up ") != NULL){
					omniCar.move(DIRECTION::UP);
					vTaskDelay(count);
				}
				if(strstr(cmd, "down ") != NULL){
					omniCar.move(DIRECTION::DOWN);
					vTaskDelay(count);
				}
				if(strstr(cmd, "turnleft ") != NULL){
					omniCar.turn(DIRECTION::LEFT);
					vTaskDelay(count);
				}
				if(strstr(cmd, "turnright ") != NULL){
					omniCar.turn(DIRECTION::RIGHT);
					vTaskDelay(count);
				}
				omniCar.stop();
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
