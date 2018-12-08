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
from SubPackage.ttsModule import tts

# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

def writeFile(isFollow):
	try:
		f = open("isFollow.txt", "w")
		f.write(str(isFollow))
		f.close()
		print ("Write file successfully")
	except Exception as error:
		print("error writing file")
		subprocess.call(["aplay", "disturbance-in-the-force.wav"])
		print(error)

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
		#print(soxOutput)
		
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
			
		uart = UartCommunication(9600)
		if (textVerify(command, ["hello", "hi", "my", "fish"])):			
			uart.actionGreeting()
			tts("Hello! How are you?")
		elif textVerify(command, ["Says", "Say"]) and textVerify(command, ["yes" ,"ok", "agree", "agrees"]):			
			uart.actionYes()
			tts("Yes")
		elif textVerify(command, ["Says", "Say"]) and textVerify(command, ["no","negative", "disagree", "disagrees"]):			
			uart.actionNo()
			tts("No")
		elif textVerify(command, ["backward", "back", "out"]):			
			uart.Send_Command_To_LPC("down 200\r\n")
			tts("Okie dokie")
		elif textVerify(command, ["forward", "come", "here"]):			
			uart.Send_Command_To_LPC("up 200\r\n")
			tts("I'm comming")
		elif textVerify(command, ["go", "move"]):			
			uart.Send_Command_To_LPC("up 600\r\n")
			tts("Woof woof")
		elif textVerify(command, ["turn", "rotate", "done"]) and textVerify(command, ["left"]):						
			uart.Send_Command_To_LPC("turnl 95\r\n")
			subprocess.call(["aplay", "WavFiles/01.wav"])
		elif textVerify(command, ["turn", "rotate", "done"]) and textVerify(command, ["right","flight","white"]):						
			uart.Send_Command_To_LPC("turnr 95\r\n")
			subprocess.call(["aplay", "WavFiles/02.wav"])
		elif textVerify(command, ["what", "what's"]) and textVerify(command, ["name"]):
			tts("My name is Wall F. At home my parent call me Fish Sauce")
		elif textVerify(command, ["what"]) and textVerify(command, ["you"]) and (not textVerify(command, ["name"])):
			tts("I'm an IOT project at Metropolia. I go around the school and streaming video back to the base station. I also using AI technology to recognize voice and face")						
		elif textVerify(command, ["introduce"]):
			tts("I'm an IOT project at Metropolia. I go around the school and streaming video back to the base station. I also using AI technology to recognize voice and face")						
		elif textVerify(command, ["follow", "following", "funny"]) and (not textVerify(command, ["stop"]):	
			writeFile(True)
			subprocess.call(["aplay", "WavFiles/I-got-a-bad-feeling-about-this.wav"])			
		elif textVerify(command, ["stop"]):		
			writeFile(False)
			subprocess.call(["aplay", "WavFiles/I-will-be-back.wav"])			
		else:
			success = False		
		
		return success
		
if __name__ == "__main__":
	while(True):
		listenForCommand(4)
