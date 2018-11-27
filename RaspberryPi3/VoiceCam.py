from SubPackage.speechRegModule import listenForCommand
from SubPackage.camModule import faceRegconition
from multiprocessing import Process
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.IN)

def camera():
	faceRegconition()
	
def microphone():
	while(True):
		if(GPIO.input(11)):
			listenForCommand(4)
	
if __name__ == "__main__":
	p = Process(target=camera)
	p2 = Process(target=microphone)
	p.start()
	p2.start()
	p.join()
	p2.join()
	