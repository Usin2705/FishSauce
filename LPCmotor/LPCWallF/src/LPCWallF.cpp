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

// TODO: global variables here
#define CAM_X_CENTER 1500
#define CAM_X_LEFT 2350
#define CAM_X_RIGHT 700

#define CAM_Y_CENTER 2380
#define CAM_Y_UP 1100

// Queue for gcode command structs
QueueHandle_t cmdQueue;
volatile uint32_t pulse_north = 0;
volatile uint32_t pulse_south = 0;
volatile uint32_t pulse_east = 0;
volatile uint32_t pulse_west = 0;
OmniCar omniCar;

// TODO: definitions and declarations here
static void vTaskReceiveRP(void *pvParameters);
static void vTaskMotor(void *pvParameters);
void carindimove(OmniCar &omnicar, WHEEL wheel, bool dir, uint32_t pulse);
void SCT_init();
int cameraMoveX(int pos);
int cameraMoveY(int pos);


int main(void) {
	cmdQueue = xQueueCreate(4, sizeof(Command));

	SCT_init();

	xTaskCreate(vTaskReceiveRP, "receiveRP",
			configMINIMAL_STACK_SIZE + 350, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);

	xTaskCreate(vTaskMotor, "motor",
			configMINIMAL_STACK_SIZE + 100, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);


	vTaskStartScheduler();
	return 1;
}

static void vTaskReceiveRP(void *pvParameters) {
	int c = 0;
	std::string str = "";
	Command cmd;
	RPSerial rpSerial;
	rpSerial.write("AT+C001", strlen("AT+C001"));
	while(1){
		c = rpSerial.read();
		if(c != EOF){
			if (c!= '\r') {
				Board_UARTPutChar(c);
				str += (char) c;
			} else {
				//Board_UARTPutSTR("\r\n");
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

static void vTaskMotor(void *pvParameters) {

	Command cmd;
	int xPos = CAM_X_CENTER;
	int yPos = CAM_Y_CENTER;
	while(1){
		if(xQueueReceive(cmdQueue, (void*) &cmd, 0)) {
			if (strcmp(cmd.cmd_type, "left") == 0) {
				carindimove(omniCar, NORTH, CLOCKWISE, cmd.count);
				carindimove(omniCar, SOUTH, COUNTERCLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "right") == 0)  {
				carindimove(omniCar, NORTH, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, SOUTH, CLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "up") == 0)  {
				carindimove(omniCar, EAST, CLOCKWISE, cmd.count);
				carindimove(omniCar, WEST, COUNTERCLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "down") == 0)  {
				carindimove(omniCar, EAST, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, WEST, CLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "turnl") == 0)  {
				carindimove(omniCar, NORTH, CLOCKWISE, cmd.count);
				carindimove(omniCar, SOUTH, CLOCKWISE, cmd.count);
				carindimove(omniCar, EAST, CLOCKWISE, cmd.count);
				carindimove(omniCar, WEST, CLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "turnr") == 0){
				carindimove(omniCar, NORTH, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, SOUTH, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, EAST, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, WEST, COUNTERCLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "turnr") == 0){
				carindimove(omniCar, NORTH, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, SOUTH, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, EAST, COUNTERCLOCKWISE, cmd.count);
				carindimove(omniCar, WEST, COUNTERCLOCKWISE, cmd.count);
			} else if (strcmp(cmd.cmd_type, "camleft") == 0){
				xPos = cameraMoveX(xPos+50);
			} else if (strcmp(cmd.cmd_type, "camright") == 0){
				xPos = cameraMoveX(xPos-50);
			} else if (strcmp(cmd.cmd_type, "camup") == 0){
				yPos = cameraMoveY(yPos - 50);
			} else if (strcmp(cmd.cmd_type, "camdown") == 0){
				yPos = cameraMoveY(yPos + 50);
			} else if (strcmp(cmd.cmd_type, "camcenter") == 0){
				xPos = cameraMoveX(CAM_X_CENTER);
				yPos = cameraMoveY(CAM_Y_CENTER);
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
	omnicar.indiMove(wheel, dir);
}

void SCT_init(){
	Chip_SCT_Init(LPC_SCTLARGE0);
	Chip_SCT_Init(LPC_SCTLARGE1);

	Chip_SWM_MovablePortPinAssign(SWM_SCT0_OUT0_O, 0,28); //Servox
	Chip_SWM_MovablePortPinAssign(SWM_SCT1_OUT0_O, 0,14); //Servoy

	LPC_SCTLARGE0->CONFIG |= (1 << 17); // two 16-bit timers, auto limit

	LPC_SCTLARGE0->CTRL_L |= (72-1) << 5; // set prescaler, SCTimer/PWM clock = 1 MHz

	LPC_SCTLARGE0->MATCHREL[0].L = 20000; // match 0 @ 10/1MHz = 10 usec (100 kHz PWM freq) (1MHz/20000)
	LPC_SCTLARGE0->MATCHREL[1].L = CAM_X_CENTER; // match 1 used for duty cycle (in 10 steps)
	LPC_SCTLARGE0->EVENT[0].STATE = 0xFFFFFFFF; // event 0 happens in all states
	LPC_SCTLARGE0->EVENT[0].CTRL = (1 << 12); // match 0 condition only
	LPC_SCTLARGE0->EVENT[1].STATE = 0xFFFFFFFF; // event 1 happens in all states
	LPC_SCTLARGE0->EVENT[1].CTRL = (1 << 0) | (1 << 12); // match 1 condition only
	LPC_SCTLARGE0->OUT[0].SET = (1 << 0); // event 0 will set SCTx_OUT0
	LPC_SCTLARGE0->OUT[0].CLR = (1 << 1); // event 1 will clear SCTx_OUT0
	LPC_SCTLARGE0->CTRL_L &= ~(1 << 2); // unhalt it by clearing bit 2 of CTRL reg


	//LPC_SCRLARGE1
	LPC_SCTLARGE1->CONFIG |= (1 << 17); // two 16-bit timers, auto limit
	LPC_SCTLARGE1->CTRL_L |= (72-1) << 5; // set prescaler, SCTimer/PWM clock = 1 MHz
	LPC_SCTLARGE1->MATCHREL[0].L = 20000; // match 0 @ 10/1MHz = 10 usec (100 kHz PWM freq) (1MHz/1000)
	LPC_SCTLARGE1->MATCHREL[1].L = 2380; // match 1 used for duty cycle (in 10 steps)
	LPC_SCTLARGE1->EVENT[0].STATE = 0xFFFFFFFF; // event 0 happens in all states
	LPC_SCTLARGE1->EVENT[0].CTRL = (1 << 12); // match 0 condition only
	LPC_SCTLARGE1->EVENT[1].STATE = 0xFFFFFFFF; // event 1 happens in all states
	LPC_SCTLARGE1->EVENT[1].CTRL = (1 << 0) | (1 << 12); // match 1 condition only
	LPC_SCTLARGE1->OUT[0].SET = (1 << 0); // event 0 will set SCTx_OUT0
	LPC_SCTLARGE1->OUT[0].CLR = (1 << 1); // event 1 will clear SCTx_OUT0
	LPC_SCTLARGE1->CTRL_L &= ~(1 << 2); // unhalt it by clearing bit 2 of CTRL reg
}

/*	Move the X Servo
 * 	2450: full left
 * 	750: full right
 * 	1500 middle
 *
 */
int cameraMoveX(int pos){
	if (pos>CAM_X_LEFT) pos = CAM_X_LEFT;
	if (pos<CAM_X_RIGHT) pos = CAM_X_RIGHT;
	LPC_SCTLARGE0->MATCHREL[1].L = pos;
	return pos;
}


/*	Move the Y Servo
 * 	2380: front
 * 	1500: top
 * 	1100: back
 *
 */
int cameraMoveY(int pos){
	if (pos > CAM_Y_CENTER) pos = CAM_Y_CENTER;
	if (pos < CAM_Y_UP) pos = CAM_Y_UP;
	LPC_SCTLARGE1->MATCHREL[1].L = pos;
	return pos;
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

	DigitalIoPin servo1(0,28,DigitalIoPin::output,true);//2.5
	DigitalIoPin servo2(0,14,DigitalIoPin::output,true);//2.5



DigitalIoPin pin5(1,6,DigitalIoPin::output,true);//2.5
DigitalIoPin pin6(0,8,DigitalIoPin::output,true);//2.5
DigitalIoPin pin11(0,10,DigitalIoPin::output,true);//2.5
DigitalIoPin pin12(1,3,DigitalIoPin::output,true);//2.5
DigitalIoPin pin13(0,0,DigitalIoPin::output,true);//2.5
DigitalIoPin pin14(0,24,DigitalIoPin::output,true);//0

DigitalIoPin pin16(0,27,DigitalIoPin::output,true);//0
DigitalIoPin pin18(0,12,DigitalIoPin::output,true);//0
 */

