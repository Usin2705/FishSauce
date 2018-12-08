import asyncio
from SubPackage.ttsModule import tts
from SubPackage.UartCommunication import UartCommunication
#from SubPackage.speechRegModule import listenForCommand
from subprocess import call

def keyboardInput():
	isTTS = False

	uart = UartCommunication(9600)
	speech = input("Press T to use text to speech.\nPress M to move.\nType exit to quit.\n")

	if speech.lower()=="t":	
		isTTS = True	
			
	while (speech.lower()!="exit"):
		if isTTS:
			speech = input("Please enter your speech:")
			if (speech.lower()!="m"):
				tts(speech)
			else:
				isTTS = False
		else:
			isTTS = uart.handleMoveKeys()
	
if __name__ == '__main__':
	keyboardInput()

		
