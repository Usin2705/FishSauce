from SubPackage.UartCommunication import UartCommunication
import time

def scanForNhan(stepLeft, stepRight, stepUp, isScanned, uart):
	if (stepLeft == 0) and (stepRight==0):
		uart.Send_Command_To_LPC("camc \r\n")
		count= 100*stepUp	
		uart.Send_Command_To_LPC("camu " +str(count)+ " \r\n")
		time.sleep(0.1)
		stepUp+=1
	
		if stepUp >= 7:
			isScanned = True
	
	if (stepLeft <=3):
		count = 100*stepLeft
		uart.Send_Command_To_LPC("caml " +str(count)+ " \r\n")
		time.sleep(0.1)
		stepLeft+=1
	else:
		count = 100*stepRight	
		uart.Send_Command_To_LPC("camr " +str(count)+ " \r\n")
		time.sleep(0.1)
		stepRight+=1
		
	if (stepRight == 6):
		stepLeft=0
		stepRight=0
		
	return stepLeft, stepRight, stepUp, isScanned
	
uart = UartCommunication(9600)
stepLeft = 0
stepRight = 0
stepUp = 0
isScanned = False
while (not isScanned):
	stepLeft, stepRight, stepUp, isScanned = scanForNhan(stepLeft, stepRight, stepUp, isScanned, uart)
	time.sleep(2)
	#print("this is stepUp: " + str(stepUp))
	