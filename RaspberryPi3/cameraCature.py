from picamera import PiCamera
from time import sleep

camera = PiCamera()

camera.start_preview()
noOfPic = 30

sleep(5)
for i in range (0,noOfPic):
    sleep(2)
    camera.capture('/home/pi/Desktop/FishSauce/Joe/{:05d}.jpg'.format(i))
    
camera.stop_preview()
