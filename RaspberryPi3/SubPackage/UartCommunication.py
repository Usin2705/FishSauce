from time import sleep
import serial
import binascii
import curses


class UartCommunication():
	
	def __init__ (self, baurate):
		# Initialize
		self.ser = serial.Serial("/dev/ttyS0", baurate, timeout = 1)		
		# Atributes
		#self.baurate = baurate
			
	# Create & send the command to the LPC1549
	def Send_Command_To_LPC(self, Command_String):
		self.ser.write(Command_String.encode('ascii'))
		print("Sent {}".format(Command_String))

	# Get the input key without pressing Enter
	def getMoveKeys(self, message):
		try:
			win = curses.initscr()
			win.keypad(True)
			win.addstr(0, 0, message)
			while True: 
				ch = win.getch()
				if ch == curses.KEY_RIGHT:
					print("RIGHT")
					ch = 59
				elif ch == curses.KEY_LEFT:
					ch = 107
				elif ch == curses.KEY_UP:
					ch = 111
				elif ch == curses.KEY_DOWN:
					ch = 108				
				
				if ch in range(32, 127):
					break
				sleep(0.1)
		except: raise
		finally:
			curses.endwin()
		return chr(ch)

	# Handle the move key input
	def handleMoveKeys(self):
		str = self.getMoveKeys("Moving: ")
		# MOVEMENT
		if str == "w":
				self.Send_Command_To_LPC("up 20\r\n")
		elif str == "s":
				self.Send_Command_To_LPC("down 20\r\n")
		elif str == "a":
				self.Send_Command_To_LPC("left 20\r\n")
		elif str == "d":
				self.Send_Command_To_LPC("right 20\r\n")
		elif str == "q":
				self.Send_Command_To_LPC("turnl 20\r\n")
		elif str == "e":
				self.Send_Command_To_LPC("turnr 20\r\n")
		# CAMERA
		elif str == ";":
				self.Send_Command_To_LPC("camright 50\r\n")
		elif str == "k": 
				self.Send_Command_To_LPC("camleft 50\r\n")
		elif str == "o":
				self.Send_Command_To_LPC("camup 50\r\n")
		elif str == "l":
				self.Send_Command_To_LPC("camdown 50\r\n")
		elif str == "c":
				self.Send_Command_To_LPC("camcenter\r\n")
				
		# CHANGE MODE
		elif str == "t":
				return True
		
		
		
		return False
		
	def actionGreeting(self):
		for i in range(0,1):
			self.Send_Command_To_LPC("camup 400\r\n")
			sleep(0.1)
			self.Send_Command_To_LPC("camright 200\r\n")
			sleep(0.1)
			self.Send_Command_To_LPC("camcenter\r\n")
			sleep(0.1)
			self.Send_Command_To_LPC("camup 400\r\n")
			sleep(0.1)
			self.Send_Command_To_LPC("camleft 200\r\n")
			sleep(0.1)
			self.Send_Command_To_LPC("camcenter\r\n")
			
	def actionNo(self):
		for i in range(0,2):			
			self.Send_Command_To_LPC("camright 300\r\n")
			sleep(0.05)
			self.Send_Command_To_LPC("camcenter\r\n")
			sleep(0.05)
			self.Send_Command_To_LPC("camleft 300\r\n")
			sleep(0.05)			
			self.Send_Command_To_LPC("camcenter\r\n")
			sleep(0.05)
			
	def actionYes(self):
		for i in range(0,3):			
			self.Send_Command_To_LPC("camup 400\r\n")
			sleep(0.05)			
			self.Send_Command_To_LPC("camcenter\r\n")
			sleep(0.05)

