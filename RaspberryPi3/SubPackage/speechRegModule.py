import io
import os
import time
import sys
import subprocess
import shlex #tts
import RPi.GPIO as GPIO
from subprocess import Popen, PIPE, STDOUT
from SubPackage.textVerifyModule import textVerify
from SubPackage.UartCommunication import UartCommunication

# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

def transcribe(duration):		
		filename = os.path.join(os.path.dirname(__file__), '/home/pi/Desktop/FishSauce/', 'speech.wav')

		#Do nothing if audio is playing
		#------------------------------------
		if isAudioPlaying():
				#print (time.strftime("%Y-%m-%d %H:%M:%S ")	+ "Audio is playing")
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
		
		#read() return a bytes object, then convert it to string using decode
		soxOutput = p.stdout.read().decode("utf-8")	
		print(soxOutput)
		
		#Maximum  amplitude text increase by 24 to start the value	
		maxAmpStart = soxOutput.find("Maximum amplitude") + 24
		
		#the value is number with about 8 digit	
		maxAmpEnd = maxAmpStart + 7
		
		
		try:
			maxAmpValue = float(soxOutput[maxAmpStart:maxAmpEnd])
			print("Maximum amplitude: {}".format(maxAmpValue))
		except ValueError:
			print("Failed to get maximum amplitude value")
			maxAmpValue = 0
		
		if maxAmpValue < 0.1 :
				#print "No sound"
				#Exit if sound below minimum amplitude
				return ""		
		
		
		#Send sound	 to Google Cloud Speech Api to interpret
		#----------------------------------------------------		
		print (time.strftime("%Y-%m-%d %H:%M:%S ")  + "Sending to google api")
		GPIO.setmode(GPIO.BOARD)
		GPIO.setup(7, GPIO.OUT)
		GPIO.output(7,True)

		os.environ["GOOGLE_APPLICATION_CREDENTIALS"]="/home/pi/Downloads/service-account-file.json"
				
		# Instantiates a client
		client = speech.SpeechClient()

		# The name of the audio file to transcribe
		file_name = os.path.join(os.path.dirname(__file__), '/home/pi/Desktop/FishSauce/', 'speech.wav')

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
		GPIO.output(7,False)
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
		
def listenForCommand(listenTime):		
		print (time.strftime("%Y-%m-%d %H:%M:%S ")	+ "Launched Speech Recognition Module.")		
		sys.stdout.flush() 
		
		print("waiting for command ..")
		if (listenTime > 15): 15		
		if (listenTime < 3): 3		
		
		command	= transcribe(listenTime)
		command = " " + command + " "
		success=False
		if command!="  ":
			print (time.strftime("%Y-%m-%d %H:%M:%S ")  + "Command:" + command)
			success=True 
		else:
			return False

		commandtts =  "pico2wave -w tts.wav "						
		uart = UartCommunication(9600)
		if (textVerify(command, ["hello", "hi", "my", "fish"])):
			commandtts+= "\"Hello! How are you?\""
			uart.actionGreeting()
		elif textVerify(command, ["Says", "Say"]) and textVerify(command, ["yes" ,"ok", "agree", "agrees"]):
			commandtts+= "\"Yes\""
			uart.actionYes()
		elif textVerify(command, ["Says", "Say"]) and textVerify(command, ["no","negative", "disagree", "disagrees"]):
			commandtts+= "\"No\""
			uart.actionNo()
		elif textVerify(command, ["backward", "back", "out"]):
			commandtts+= "\"Okie dokie\""
			uart.Send_Command_To_LPC("down 200\r\n")
		elif textVerify(command, ["forward", "come", "here"]):
			commandtts+= "\"I'm comming\""
			uart.Send_Command_To_LPC("up 200\r\n")
		elif textVerify(command, ["turn", "rotate", "done"]) and textVerify(command, ["left"]):			
			commandtts+= "\"Woof woof\""
			uart.Send_Command_To_LPC("turnl 95\r\n")
		elif textVerify(command, ["turn", "rotate", "done"]) and textVerify(command, ["right","flight","white"]):			
			commandtts+= "\"alright alright\""
			uart.Send_Command_To_LPC("turnr 95\r\n")
		else:
			success = False
		
		print(commandtts)
		if success:
			#if success then play text to speech:		
			args = shlex.split(commandtts)
			subprocess.call (args)
			# better quality for pico2wave
			#https://askubuntu.com/questions/853200/improve-sound-not-voice-quality-of-pico2wave-text-to-speech
			commandtts = "play -qV0 tts.wav treble 24 gain -l 6"
			args = shlex.split(commandtts)
			subprocess.call (args)
		
		return success
		
if __name__ == "__main__":
	while(True):
		listenForCommand(4)
