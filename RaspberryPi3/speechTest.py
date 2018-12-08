from SubPackage.speechRegModule import listenForCommand

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.IN)

if __name__ == "__main__":
	while(True):
		if(GPIO.input(11)):
			listenForCommand(4)
