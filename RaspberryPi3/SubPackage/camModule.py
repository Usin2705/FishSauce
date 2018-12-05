# USAGE
# python pi_face_recognition.py --cascade haarcascade_frontalface_default.xml --encodings encodings.pickle

# import the necessary packages
from imutils.video import VideoStream
from imutils.video import FPS
import face_recognition
import argparse
import imutils
import pickle
import time
import cv2
import subprocess
from SubPackage.UartCommunication import UartCommunication

def scanForNhan(stepLeft, stepRight, stepUp, isScanned, uart):
	if (stepLeft == 0) and (stepRight==0):
		uart.Send_Command_To_LPC("camc \r\n")
		count= 100*stepUp	
		uart.Send_Command_To_LPC("camu " +str(count)+ " \r\n")
		time.sleep(0.1)
		stepUp+=1
	
		if stepUp >= 7:
			isScanned = True
	
	if (stepLeft <=3):
		count = 100*stepLeft
		uart.Send_Command_To_LPC("caml " +str(count)+ " \r\n")
		time.sleep(0.1)
		stepLeft+=1
	else:
		count = 100*stepRight	
		uart.Send_Command_To_LPC("camr " +str(count)+ " \r\n")
		time.sleep(0.1)
		stepRight+=1
		
	if (stepRight == 6):
		stepLeft=0
		stepRight=0
		
	return stepLeft, stepRight, stepUp, isScanned

def faceRegconition():
	# construct the argument parser and parse the arguments
	ap = argparse.ArgumentParser()
	ap.add_argument("-c", "--cascade", default = "haarcascade_frontalface_default.xml",
					help = "path to where the face cascade resides")
	ap.add_argument("-e", "--encodings", default = "encodings.pickle",
					help="path to serialized db of facial encodings")
	args = vars(ap.parse_args())

	# load the known faces and embeddings along with OpenCV's Haar
	# cascade for face detection
	print("[INFO] loading encodings + face detector...")
	data = pickle.loads(open(args["encodings"], "rb").read())
	detector = cv2.CascadeClassifier(args["cascade"])

	# initialize the video stream and allow the camera sensor to warm up
	print("[INFO] starting video stream...")
	#for USB camera
	# vs = VideoStream(src=0).start()

	#for pi camera
	vs = VideoStream(usePiCamera=True).start()
	time.sleep(2.0)

	# start the FPS counter
	fps = FPS().start()
	startTime = time.time()
	
	stepLeft = 0
	stepRight = 0
	stepUp = 0
	isScanned = False
	isSaid = False
	countForDetect = 0	                      
	uart = UartCommunication(9600)
	
	# loop over frames from the video file stream
	while True:
		countForDetect+=1
		# grab the frame from the threaded video stream and resize it
		# to 500px (to speedup processing)
		frame = vs.read()
		frame = imutils.resize(frame, width=400)
		
		# convert the input frame from (1) BGR to grayscale (for face
		# detection) and (2) from BGR to RGB (for face recognition)
		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

		# detect faces in the grayscale frame
		rects = detector.detectMultiScale(gray, scaleFactor=1.1, 
			minNeighbors=5, minSize=(30, 30),
			flags=cv2.CASCADE_SCALE_IMAGE)

		# OpenCV returns bounding box coordinates in (x, y, w, h) order
		# but we need them in (top, right, bottom, left) order, so we
		# need to do a bit of reordering
		boxes = [(y, x + w, y + h, x) for (x, y, w, h) in rects]

		# compute the facial embeddings for each face bounding box
		encodings = face_recognition.face_encodings(rgb, boxes)
		names = []

		# loop over the facial embeddings
		for encoding in encodings:
			# attempt to match each face in the input image to our known
			# encodings
			matches = face_recognition.compare_faces(data["encodings"],
				encoding, tolerance=0.4)
			name = "Unknown"

			# check to see if we have found a match
			if True in matches:
				# find the indexes of all matched faces then initialize a
				# dictionary to count the total number of times each face
				# was matched
				matchedIdxs = [i for (i, b) in enumerate(matches) if b]
				counts = {}

				# loop over the matched indexes and maintain a count for
				# each recognized face face
				for i in matchedIdxs:
					name = data["names"][i]
					counts[name] = counts.get(name, 0) + 1

				# determine the recognized face with the largest number
				# of votes (note: in the event of an unlikely tie Python
				# will select first entry in the dictionary)
				name = max(counts, key=counts.get)
			
			# update the list of names
			names.append(name)

		# loop over the recognized faces
		for ((top, right, bottom, left), name) in zip(boxes, names):
			# draw the predicted face name on the image
			cv2.rectangle(frame, (left, top), (right, bottom),
				(0, 255, 0), 2)
			y = top - 15 if top - 15 > 15 else top + 15
			xAdjust = (right + left)
			yAdjust = (top + bottom)
			cv2.putText(frame, name, (left, y), cv2.FONT_HERSHEY_SIMPLEX,
				0.75, (0, 255, 0), 2)
			
			if name=="NhanPhan":
				if (isSaid):					
					subprocess.call(["aplay", "WavFiles/hello-there.wav"])
				stepLeft = 0
				stepRight = 0
				stepUp = 0
				isScanned = False
				isSaid = False
				startTime = time.time()  
				#based on 800x600
				#800->950
				if (xAdjust) > 575:
						uart.Send_Command_To_LPC("camr 100\r\n")
						time.sleep(0.05)   
				elif (xAdjust) > 475:
						uart.Send_Command_To_LPC("camr 40\r\n")
						time.sleep(0.05)
				elif (xAdjust) < 225:
						uart.Send_Command_To_LPC("caml 100\r\n")
						time.sleep(0.05)
				elif (xAdjust) < 325:
						uart.Send_Command_To_LPC("caml 40\r\n")
						time.sleep(0.05)
				#600->700
				if (yAdjust) > 450:
						uart.Send_Command_To_LPC("camd 100\r\n")
						time.sleep(0.05)    
				elif (yAdjust) > 350:
						uart.Send_Command_To_LPC("camd 40\r\n")
						time.sleep(0.05)
				elif (yAdjust) < 180:
						uart.Send_Command_To_LPC("camu 100\r\n")
						time.sleep(0.05)
				elif (yAdjust) < 250:
						uart.Send_Command_To_LPC("camu 40\r\n")
						time.sleep(0.05)

							
		elapsedTime = time.time() - startTime
		
		if (elapsedTime > 30) and (not isScanned) and (countForDetect >=3):	
			countForDetect = 0
			if (not isSaid):
				subprocess.call(["/usr/bin/amixer", "cset", "numid=1", "100%"])
				subprocess.call(["aplay", "WavFiles/I-will-look-for-you.wav"])

				isSaid = True
			stepLeft, stepRight, stepUp, isScanned = scanForNhan(stepLeft, stepRight, stepUp, isScanned, uart)
		
		#If finish and can't find my face
		if (isScanned):
			uart.Send_Command_To_LPC("camc\r\n")
		# display the image to our screen
		cv2.imwrite("camera.jpg", frame)
		cv2.imshow("Frame", frame)
		key = cv2.waitKey(1) & 0xFF

		# if the `q` key was pressed, break from the loop
		if key == ord("q"):
			break

		# update the FPS counter
		fps.update()

	# stop the timer and display FPS information
	fps.stop()
	print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
	print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

	# do a bit of cleanup
	cv2.destroyAllWindows()
	vs.stop()
	
if __name__ == "__main__":
	faceRegconition()