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
			win.addstr(0, 0, message)
			while True: 
				ch = win.getch()
				if ch in range(32, 127): break
				sleep(0.05)
		except: raise
		finally:
			curses.endwin()
		return chr(ch)

	# Handle the move key input
	def handleMoveKeys(self):
		str = self.getMoveKeys("Moving: ").lower();
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
		elif str == "t":
				return True
		
		return False


