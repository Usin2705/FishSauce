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

// TODO: global variables here
#define CAM_X_CENTER 1500
#define CAM_X_LEFT 2350
#define CAM_X_RIGHT 700

#define CAM_Y_CENTER 2380
#define CAM_Y_UP 1100

// Queue for gcode command structs
QueueHandle_t cmdQueue;
QueueHandle_t obstacleQueue;
volatile uint32_t pulse_north = 0;
volatile uint32_t pulse_south = 0;
volatile uint32_t pulse_east = 0;
volatile uint32_t pulse_west = 0;
OmniCar omniCar;

// TODO: definitions and declarations here
static void vTaskReceiveRP(void *pvParameters);
static void vTaskReceiveHC(void *pvParameters);
static void vTaskMotor(void *pvParameters);
void carindimove(OmniCar &omnicar, WHEEL wheel, bool dir, uint32_t pulse);
void SCT_init();
void SCT0_Init();
int cameraMoveX(int pos);
int cameraMoveY(int pos);
static void prvSetupHardware();

int main(void) {
	cmdQueue = xQueueCreate(4, sizeof(Command));
	obstacleQueue = xQueueCreate(1, sizeof(bool));
	prvSetupHardware();
	SCT_init();
	SCT0_Init();
	xTaskCreate(vTaskReceiveRP, "receiveRP",
			configMINIMAL_STACK_SIZE + 350, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);

	xTaskCreate(vTaskReceiveHC, "receiveHC",
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
			} else if (strcmp(cmd.cmd_type, "caml") == 0){
				xPos = cameraMoveX(xPos + cmd.count);
			} else if (strcmp(cmd.cmd_type, "camr") == 0){
				xPos = cameraMoveX(xPos - cmd.count);
			} else if (strcmp(cmd.cmd_type, "camu") == 0){
				yPos = cameraMoveY(yPos - cmd.count);
			} else if (strcmp(cmd.cmd_type, "camd") == 0){
				yPos = cameraMoveY(yPos + cmd.count);
			} else if (strcmp(cmd.cmd_type, "camm") == 0){
				xPos = cameraMoveX(CAM_X_CENTER);
			} else if (strcmp(cmd.cmd_type, "camf") == 0){
				xPos = cameraMoveX(CAM_X_CENTER);
				yPos = cameraMoveY(2100);
			} else if (strcmp(cmd.cmd_type, "camc") == 0){
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

void SCT0_Init()
{
	Chip_INMUX_SelectSCT0Src(0, SCT0_INMUX_PIO1_6);			// SCT2_IN0 at P1_6
	Chip_INMUX_SelectSCT0Src(1, SCT0_INMUX_PIO1_7);			// SCT2_IN0 at P1_7

	LPC_SYSCON->SYSAHBCLKCTRL[0] |= (1 << 2);                			// enable the SCT0 clock
	LPC_SCT0->CONFIG           |= (1 << 0);			      			// unified

	LPC_SCT0->CTRL_U        |= (72 << 5);       					// set pre-scaler

	LPC_SCT0->REGMODE_L      = (1 << 0) | (1 << 1)
							 | (1 << 2) | (1 << 3);        			// CAP 0 and CAP 1


	LPC_SCT0->EVENT[1].STATE = 0xFFFFFFFF;                 			// event 1 happens in all states
	LPC_SCT0->EVENT[1].CTRL  = (1 << 10) | (2 << 12);      			// IN_0 rising edge condition only

	LPC_SCT0->EVENT[2].STATE = 0xFFFFFFFF;                 			// event 2 happens in all states
	LPC_SCT0->EVENT[2].CTRL  = (2 << 10) | (2 << 12);      			// IN_0 falling edge condition only

	LPC_SCT0->EVENT[3].STATE = 0xFFFFFFFF;                 			// event 3 happens in all states
	LPC_SCT0->EVENT[3].CTRL  = (1 << 10) | (2 << 12) | (1 << 6);    // IN_1 rising edge condition only

	LPC_SCT0->EVENT[4].STATE = 0xFFFFFFFF;                 			// event 4 happens in all states
	LPC_SCT0->EVENT[4].CTRL  = (2 << 10) | (2 << 12) | (1 << 6);    // IN_1 falling edge condition only

	LPC_SCT0->CAPCTRL[0].U   = (1 << 1);                   			// event 1 is causing capture 0
	LPC_SCT0->CAPCTRL[1].U   = (1 << 2);       			   			// event 2 cause capture 1
	LPC_SCT0->CAPCTRL[2].U   = (1 << 3);                   			// event 3 is causing capture 2
	LPC_SCT0->CAPCTRL[3].U   = (1 << 4);       			   			// event 4 cause capture 3

	LPC_SCT0->OUT[0].SET     = (1 << 1);                   			// event 1 set   OUT0 LED ON
	LPC_SCT0->OUT[0].CLR     = (1 << 2);                   			// event 2 clear OUT0 LED OFF

	LPC_SCT0->EVEN           = (1 << 2) | (1 << 4);        		   			// event 2 generate an irq

	NVIC_EnableIRQ(SCT0_IRQn);                             			// enable SCT0 interrupt

	LPC_SCT0->CTRL_U           &= ~(1 << 2);               			// start timer
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

static void prvSetupHardware()
{
	SystemCoreClockUpdate();
	Board_Init();

	LPC_SYSCON->SYSAHBCLKCTRL[0] |= (1<<12)    |         // enable SWM clock
			(1<<14)  |         // enable GPIO port 0 clock
			(1<<15)  |         // enable GPIO port 1 clock
			(1<<11)  |         // enable PMUX clock
			(1<<13);           // enable IOCON clock

	LPC_SWM->PINASSIGN[7]        |= 0x00FFFF00;          // ASSIGN7(23:8) = FFFF
	LPC_SWM->PINASSIGN[7]        &= 0xFF1800FF;          // SCT0_OUT0 = P0.0  = timeout (red LED)
	// SCT0_OUT1 = P0.24 = width_error (green LED)
//	LPC_PMUX->SCT0_P_MUX0       = 2;                   // SCT0_IN2  = P0.17 = SW1

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

void SCT0_IRQHandler(void)
{
	uint32_t status = LPC_SCT0->EVFLAG;
	uint32_t time, time2;
	bool isBlocked = false;
	BaseType_t xHigherPriorityTaskWoken;
	if(status & (1 << 2)) {
		if(LPC_SCT0->CAP[1].U >= LPC_SCT0->CAP[0].U) {
			time = LPC_SCT0->CAP[1].U - LPC_SCT0->CAP[0].U;
		}
		else {															//The counter has been reset
			time = 4294967295 - LPC_SCT0->CAP[0].U + LPC_SCT0->CAP[1].U;
		}
		time = (double)time*17.0/1000.0;
		if(time <= 25.0)
			isBlocked = true;
		else isBlocked  = false;
	}
	if(status & (1 << 4)) {
		if(LPC_SCT0->CAP[3].U >= LPC_SCT0->CAP[2].U) {
			time2 = LPC_SCT0->CAP[3].U - LPC_SCT0->CAP[2].U;
		}
		else {															//The counter has been reset
			time2 = 4294967295 - LPC_SCT0->CAP[2].U + LPC_SCT0->CAP[3].U;
		}
		time2 = (double)time2*17.0/1000.0;
		if(time2 <= 25.0)
			isBlocked = true;
		else isBlocked  = false;
	}
	//xQueueSendFromISR(obstacleQueue, &isBlocked, &xHigherPriorityTaskWoken);
	LPC_SCT0->EVFLAG = status;                         				// Acknowledge interrupts
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


	//UART1 RPi
	DigitalIoPin pin11(0,10,DigitalIoPin::output,true);//2.5
	DigitalIoPin pin12(1,3,DigitalIoPin::output,true);//2.5

	//UART2 Control
	DigitalIoPin pin6(0,8,DigitalIoPin::output,true);//2.5

	DigitalIoPin pin5(1,6,DigitalIoPin::output,true);//2.5
	DigitalIoPin pin13(0,0,DigitalIoPin::output,true);//2.5

DigitalIoPin pin14(0,24,DigitalIoPin::output,true);//0
DigitalIoPin pin16(0,27,DigitalIoPin::output,true);//0
DigitalIoPin pin18(0,12,DigitalIoPin::output,true);//0
 */

