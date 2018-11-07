/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */
#include <cr_section_macros.h>

#include "FreeRTOS.h"
#include "task.h"
#include <cstring>
#include "DigitalIoPin.h"
#include "OmniCar.h"
#include "Command.h"
#include "queue.h"
#include "ITM_write.h"
#include "string"
#include "RPSerial.h"
#include "HCSerial.h"
#define USEHC 1

// TODO: global variables here
// Queue for gcode command structs
QueueHandle_t cmdQueue;
volatile uint32_t pulse_north = 0;
volatile uint32_t pulse_south = 0;
volatile uint32_t pulse_east = 0;
volatile uint32_t pulse_west = 0;
OmniCar omniCar;

// TODO: definitions and declarations here
//static void vTaskReceiveRP(void *pvParameters);
static void vTaskReceiveHC(void *pvParameters);
static void vTaskMotor(void *pvParameters);
void carindimove(OmniCar &omnicar, WHEEL wheel, bool dir, uint32_t pulse);


int main(void) {
	cmdQueue = xQueueCreate(4, sizeof(Command));

#if !USEHC
	xTaskCreate(vTaskReceiveRP, "receiveRP",
			configMINIMAL_STACK_SIZE + 350, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);
#endif
#if USEHC
	xTaskCreate(vTaskReceiveHC, "receiveHC",
			configMINIMAL_STACK_SIZE + 350, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);
#endif
	xTaskCreate(vTaskMotor, "motor",
			configMINIMAL_STACK_SIZE + 100, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);


	vTaskStartScheduler();
	return 1;
}

#if !USEHC
static void vTaskReceiveRP(void *pvParameters) {
	int c = 0;
	std::string str = "";
	Command cmd;
	RPSerial rpSerial;
	while(1){
		c = rpSerial.read();
		if(c != EOF){
			if (c!= '\r') {
				Board_UARTPutChar(c);
				str += (char) c;
			} else {
				Board_UARTPutSTR("\r\n");
				sscanf(str.c_str(),"%s %d",cmd.cmd_type,&cmd.count);
				if(xQueueSendToBack(cmdQueue, &cmd, portMAX_DELAY) == pdPASS){
				} else {
					ITM_write("Cannot Send to the Queue\r\n");
				}

				str = "";
			}
		}
	}
}
#endif
#if USEHC
static void vTaskReceiveHC(void *pvParameters) {
	int c = 0;
	std::string str = "";
	Command cmd;
	HCSerial hcSerial;
	hcSerial.write("AT+C001", strlen("AT+C001"));
	while(1){
		c = hcSerial.read();
		if(c != EOF){
			if (c!= '\r') {
				Board_UARTPutChar(c);
				str += (char) c;
			} else {
				Board_UARTPutSTR("\r\n");
				sscanf(str.c_str(),"%s %d",cmd.cmd_type,&cmd.count);
				if(xQueueSendToBack(cmdQueue, &cmd, portMAX_DELAY) == pdPASS){
				} else {
					ITM_write("Cannot Send to the Queue\r\n");
				}

				str = "";
			}
		}
	}
}
#endif

static void vTaskMotor(void *pvParameters) {

	Command cmd;

	while(1){
		if(xQueueReceive(cmdQueue, (void*) &cmd, 0)) {
			if (strcmp(cmd.cmd_type, "left") == 0) {
				carindimove(omniCar, NORTH, CLOCKWISE, 100);
				carindimove(omniCar, SOUTH, COUNTERCLOCKWISE, 100);
			} else if (strcmp(cmd.cmd_type, "right") == 0)  {
				carindimove(omniCar, NORTH, COUNTERCLOCKWISE, 100);
				carindimove(omniCar, SOUTH, CLOCKWISE, 100);
			} else if (strcmp(cmd.cmd_type, "up") == 0)  {
				carindimove(omniCar, EAST, CLOCKWISE, 100);
				carindimove(omniCar, WEST, COUNTERCLOCKWISE, 100);
			} else if (strcmp(cmd.cmd_type, "down") == 0)  {
				carindimove(omniCar, EAST, COUNTERCLOCKWISE, 100);
				carindimove(omniCar, WEST, CLOCKWISE, 100);
			} else if (strcmp(cmd.cmd_type, "turnl") == 0)  {
				carindimove(omniCar, NORTH, CLOCKWISE, 100);
				carindimove(omniCar, SOUTH, CLOCKWISE, 100);
				carindimove(omniCar, EAST, CLOCKWISE, 100);
				carindimove(omniCar, WEST, CLOCKWISE, 100);
			} else if (strcmp(cmd.cmd_type, "turnr") == 0){
				carindimove(omniCar, NORTH, COUNTERCLOCKWISE, 100);
				carindimove(omniCar, SOUTH, COUNTERCLOCKWISE, 100);
				carindimove(omniCar, EAST, COUNTERCLOCKWISE, 100);
				carindimove(omniCar, WEST, COUNTERCLOCKWISE, 100);
			}
		}
	}
}

void carindimove(OmniCar &omnicar, WHEEL wheel, bool dir, uint32_t pulse) {
	switch(wheel) {
	case NORTH:
		pulse_north = pulse;
		break;
	case SOUTH:
		pulse_south = pulse;
		break;
	case EAST:
		pulse_east = pulse;
		break;
	case WEST:
		pulse_west = pulse;
		break;
	}
	omnicar.indimove(wheel, dir);
}

extern "C" {

void PIN_INT0_IRQHandler(void)			//north
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(0));
	if(pulse_north > 0) {
		pulse_north--;
	}
	else omniCar.stopWheel(NORTH);
}
void PIN_INT1_IRQHandler(void)			//south
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));
	if(pulse_south > 0) {
		pulse_south--;

	}
	else omniCar.stopWheel(SOUTH);
}
void PIN_INT2_IRQHandler(void)			//east
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(2));
	if(pulse_east > 0) {
		pulse_east--;
	}
	else omniCar.stopWheel(EAST);
}
void PIN_INT3_IRQHandler(void)			//west
{
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(3));
	if(pulse_west > 0) {
		pulse_west--;
	}
	else omniCar.stopWheel(WEST);
}

void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

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

	DigitalIoPin intsouthpin20(0,23,DigitalIoPin::output,true);//3.2
	DigitalIoPin intwestpin21(0,22,DigitalIoPin::output,true);//3.2
	DigitalIoPin inteastpin15(1,0,DigitalIoPin::output,true);//2.5
	intnorth  0 0

DigitalIoPin pin5(1,6,DigitalIoPin::output,true);//2.5
DigitalIoPin pin6(0,8,DigitalIoPin::output,true);//2.5
DigitalIoPin pin11(0,10,DigitalIoPin::output,true);//2.5
DigitalIoPin pin12(1,3,DigitalIoPin::output,true);//2.5
DigitalIoPin pin13(0,0,DigitalIoPin::output,true);//2.5
DigitalIoPin pin14(0,24,DigitalIoPin::output,true);//0

DigitalIoPin pin16(0,27,DigitalIoPin::output,true);//0
DigitalIoPin pin17(0,28,DigitalIoPin::output,true);//2.5
DigitalIoPin pin18(0,12,DigitalIoPin::output,true);//0
DigitalIoPin pin19(0,14,DigitalIoPin::output,true);//2.5


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

