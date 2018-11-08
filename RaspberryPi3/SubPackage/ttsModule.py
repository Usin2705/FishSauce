import subprocess
import shlex #tts

def tts(text):	

	commandtts =  "pico2wave -w tts.wav "	
	commandtts+="\""
	commandtts+=text
	commandtts+="\""
	print(commandtts)
	args = shlex.split(commandtts)
	subprocess.call (args)
	# better quality for pico2wave
	#https://askubuntu.com/questions/853200/improve-sound-not-voice-quality-of-pico2wave-text-to-speech
	commandtts = "play -qV0 tts.wav treble 24 gain -l 6"
	args = shlex.split(commandtts)
	subprocess.call (args)