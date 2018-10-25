import sys
from time import sleep

def capture(system):
	noOfPic = 30
	if system == "win":
		import cv2
		camera = cv2.VideoCapture(0)		

		for i in range (0,noOfPic):
			sleep(2)
			retval, frame = camera.read()
			if retval != True:
				raise ValueError("Can't read frame")
			cv2.imwrite('D/Desktop/Projects/FishSauce/NhanPhan/{:05d}.jpg'.format(i), frame)
			cv2.imshow("img1", frame)
			cv2.waitKey()
	else:
		from picamera import PiCamera		
		camera = PiCamera()
		camera.start_preview()
		sleep(5)
		for i in range (0,noOfPic):
			sleep(2)
			camera.capture('/home/pi/Desktop/FishSauce/Joe/{:05d}.jpg'.format(i))    
		camera.stop_preview()

if __name__ == "__main__":
	import argparse
	argparse = argparse.ArgumentParser()	
	argparse.add_argument("--system", default = "pi", help = "Operating system")
	args = argparse.parse_args()
	if args.system == "win":
		print ("Using windows to take picture")	
	capture(args.system)