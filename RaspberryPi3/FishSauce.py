#import asyncio
from SubPackage.ttsModule import tts
from SubPackage.UartCommunication import UartCommunication
from subprocess import call

isTTS = False

uart = UartCommunication(9600)
call(["/usr/bin/amixer", "cset", "numid=1", "90%"])
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
		
