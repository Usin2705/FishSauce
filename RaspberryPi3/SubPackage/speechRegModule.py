import io
import os
import time
import sys
import subprocess
import shlex #tts
from subprocess import Popen, PIPE, STDOUT
import paho.mqtt.client as mqtt # for mqtt

# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

def transcribe(duration):
		filename = 'speech.wav'

		#Do nothing if audio is playing
		#------------------------------------
		if isAudioPlaying():
				#print time.strftime("%Y-%m-%d %H:%M:%S ")	+ "Audio is playing"
				return ""
				
		#Record sound
		#----------------

		print("listening ..")
		os.system(
			'arecord -D plughw:1,0 -f cd -c 1 -t wav -d ' + str(duration) + '  -q -r 16000 ' + filename)
				
		#Check if the amplitude is high enough
		#---------------------------------------
		cmd = 'sox ' + filename + ' -n stat'
		p = Popen(cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		soxOutput = p.stdout.read()
		#print "Popen output" + soxOutput

		
		maxAmpStart = soxOutput.find("Maximum amplitude")+24
		maxAmpEnd = maxAmpStart + 7
		
		#print "Max Amp Start: " + str(maxAmpStart)
		#print "Max Amop Endp: " + str(maxAmpEnd)

		maxAmpValueText = soxOutput[maxAmpStart:maxAmpEnd]
		
		
		print "Max Amp: " + maxAmpValueText

		maxAmpValue = float(maxAmpValueText)

		if maxAmpValue < 0.05 :
				#print "No sound"
				#Exit if sound below minimum amplitude
				return ""		
		

		#Send sound	 to Google Cloud Speech Api to interpret
		#----------------------------------------------------
		
		print time.strftime("%Y-%m-%d %H:%M:%S ")  + "Sending to google api"


		os.environ["GOOGLE_APPLICATION_CREDENTIALS"]="/home/pi/Downloads/service-account-file.json"
				
		# Instantiates a client
		client = speech.SpeechClient()

		# The name of the audio file to transcribe
		file_name = os.path.join(os.path.dirname(__file__), '/home/pi/Desktop/lpcVen/', 'test.wav')

		# Loads the audio into memory
		with io.open(file_name, 'rb') as audio_file:
				content = audio_file.read()
				audio = types.RecognitionAudio(content=content)

		config = types.RecognitionConfig(
				encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
				sample_rate_hertz=16000,
				language_code='en-US')

		# Detects speech in the audio file
		response = client.recognize(config, audio)
		print(response)
	
		if not response.results:
				return ""
		else:
				return response.results[0].alternatives[0].transcript
				
def isAudioPlaying():
		
		audioPlaying = False 

		#Check processes using ps
		#---------------------------------------
		cmd = 'ps -C omxplayer,mplayer'
		lineCounter = 0
		p = Popen(cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)

		for ln in p.stdout:
				lineCounter = lineCounter + 1
				if lineCounter > 1:
						audioPlaying = True
						break

		return audioPlaying ; 
		
def listenForCommand(client):
		global isHandControl
		global handSpeed
		global isNewHandCommand
		#print("waiting for command ..")
		command	 = transcribe(3)
		command = " " + command + " "
		
		if command!="  ":
			print time.strftime("%Y-%m-%d %H:%M:%S ")  + "Command: " + command 

		success=True 

		commandtts =  "pico2wave -w tts.wav "				
		
		picommand = ""
		
		if isHandControl:		
			if isNewHandCommand and picommand != "M":
				isNewHandCommand = False
				if handSpeed == 0:
					picommand = "a" 
				elif handSpeed == 1:
					picommand = "c"
				elif handSpeed == 2:
					picommand = "f"				
				elif handSpeed == 3:
					picommand = "h"
					
			
					
			if command.lower().find(" hand ")>-1 or command.lower().find("hand control")>-1 or command.lower().find("mqtt")>-1 or command.lower().find("hunt")>-1:
				commandtts+= "\"Turn off hand control\""
				isHandControl = False
			else:	
				#sucess = false to not say anything
				if picommand != "":
					Send_Command_To_LPC(picommand)
					return True

				success = False
				return success
				#if not success then said hand control is on, speak control is off
				#commandtts+= "\"Hand control mode is on. Say ... hand control to turn it off first.\"" 
			
		else:
			if command.lower().find(" 1 ")>-1:
				commandtts+= "\"Set unit to: 1\""
				picommand = "1"			
			elif command.lower().find(" 2 ")>-1:
				commandtts+= "\"Set unit to: 2\""
				picommand = "2"
			elif command.lower().find(" 3 ")>-1:
				commandtts+= "\"Set unit to: 3\""
				picommand = "3"
			elif command.lower().find(" 4 ")>-1:
				commandtts+= "\"Set unit to: 4\""
				picommand = "4"
			elif command.lower().find(" 5 ")>-1:
				commandtts+= "\"Set unit to: 5\""
				picommand = "5"
			elif command.lower().find(" 6 ")>-1:
				commandtts+= "\"Set unit to: 6\""
				picommand = "6"
			elif command.lower().find(" 7 ")>-1:
				commandtts+= "\"Set unit to: 7\""
				picommand = "7"
			elif command.lower().find(" 8 ")>-1:
				commandtts+= "\"Set unit to: 8\""
				picommand = "8"
			elif command.lower().find(" 9 ")>-1:
				commandtts+= "\"Set unit to: 9\""
				picommand = "9"
			elif command.lower().find(" 10 ")>-1:
				commandtts+= "\"Set unit to: 10\""
				picommand = "T"
			elif command.lower().find(" off ")>-1 or command.lower().find(" shut ")>-1 or command.lower().find(" stop ")>-1 :
				commandtts+= "\"Shuting down Air ventilation system\""
				picommand = "X"
			elif (command.lower().find(" on ")>-1  or command.lower().find(" start ")>-1 or command.lower().find(" thought ")>-1 or command.lower().find(" begin ")>-1) and command.lower().find(" step ")< 0:
				commandtts+= "\"Starting Air ventilation system\""
				picommand = "O"
			elif command.lower().find("auto")>-1 or command.lower().find("ulti")>-1:
				commandtts+= "\"Set control mode to: Auto\""
				picommand = "A"
			elif command.lower().find("manual")>-1	:
				commandtts+= "\"Set control mode to: Manual\""
				picommand = "M"
			elif command.lower().find(" 20 ")>-1  :
				commandtts+= "\"Set control value to: 20\""
				picommand = "a"
			elif command.lower().find(" 30 ")>-1  :
				commandtts+= "\"Set control value to: 30\""
				picommand = "b"
			elif command.lower().find(" 40 ")>-1 or command.lower().find("faulty")>-1 :
				commandtts+= "\"Set control value to: 40\""
				picommand = "c"
			elif command.lower().find(" 50 ")>-1  :
				commandtts+= "\"Set control value to: 50\""
				picommand = "d"			
			elif command.lower().find(" 60 ")>-1  :
				commandtts+= "\"Set control value to: 60\""
				picommand = "e"
			elif command.lower().find(" 70 ")>-1  :
				commandtts+= "\"Set control value to: 70\""
				picommand = "f" 
			elif command.lower().find(" 80 ")>-1  :
				commandtts+= "\"Set control value to: 80\""
				picommand = "g"
			elif command.lower().find(" 90 ")>-1 or command.lower().find(" nighty ")>-1 :
				commandtts+= "\"Set control value to: 90\""
				picommand = "h"
			elif command.lower().find(" 100 ")>-1  :
				commandtts+= "\"Set control value to: 100\""
				picommand = "i"			
			elif command.lower().find(" hand ")>-1 or command.lower().find("hand control")>-1 or command.lower().find("mqtt")>-1:
				isHandControl = True				
				commandtts+= "\"Using hand to control the fan speed.\""
				picommand = "M"
			else:
					#if not success then play I don't understand and return False			
					success = False
					if command.find("  ") == -1 :
							subprocess.call(["aplay", "i-dont-understand.wav"])
					return success 
		
		#if success then play text to speech:		
		args = shlex.split(commandtts)
		subprocess.call (args)
		# better quality for pico2wave
		#https://askubuntu.com/questions/853200/improve-sound-not-voice-quality-of-pico2wave-text-to-speech
		commandtts = "play -qV0 tts.wav treble 24 gain -l 6"
		args = shlex.split(commandtts)
		subprocess.call (args)
		commandtts = ""
		if picommand != "":
			Send_Command_To_LPC(picommand)
					
		return success 
		
		
# Create & send the command to the LPC1549
def Send_Command_To_LPC(Command_String):
	#global err_cnt
	#Command_String = Command_String
	ser.write(Command_String.encode('ascii'))
	#sleep(.1)
	#Val1 = Steps + ","
	#ser.write(Val1.encode('ascii'))
	#sleep(.2)
	#Val2 = SPS\
	#Check_Val = Command_String + Val1 + Val2
	#Val2 = Val2 + "\n"
	#ser.write(Val2.encode('ascii'))
	print("Sent " + Command_String.encode('ascii'))
		
print (time.strftime("%Y-%m-%d %H:%M:%S ")	+ "Launched speechAnalyser.py")

#Start up code to open the serial port
ser = serial.Serial("/dev/ttyS0",9600, timeout =1)
if ser.isOpen():
	print(ser.name, "is open")
	print(ser)

	
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
client.connect(MQTT_SERVER, MQTT_PORT, 60)

while True:
				
		sys.stdout.flush() 
		listenForCommand(client)
		client.loop(0.1)
		#Listen for trigger word
		#spokenText = transcribe(2) ;
		
		#if len(spokenText) > 0: 
				#print time.strftime("%Y-%m-%d %H:%M:%S ")	+ "Trigger word: " + spokenText

		#triggerWordIndex  = spokenText.lower().find("alexa")

		#if triggerWordIndex >-1:
				#If trigger word found, listen for command 
				#subprocess.call(["aplay", "beep-3.wav"])
				#success = listenForCommand()	
				
				#if not success:
						#subprocess.call(["aplay", "beep-3.wav"])
						#listenForCommand()
