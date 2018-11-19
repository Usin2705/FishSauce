import asyncio
from SubPackage.ttsModule import tts
from SubPackage.UartCommunication import UartCommunication
#from SubPackage.speechRegModule import listenForCommand
from subprocess import call

async def keyboardInput():
	await asyncio.sleep(0)
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

#async def speechTask():
	#await asyncio.sleep(5)
	#listenForCommand()
	#await asyncio.sleep(5)
	
if __name__ == '__main__':
	kbTask = asyncio.ensure_future(keyboardInput())
	#spTask = asyncio.ensure_future(speechTask())
	loop = asyncio.get_event_loop()
	loop.run_forever()

		
