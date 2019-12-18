# Wall-F
<b>IoT project 2018</b>  
Metropolia UAS, 2018.  
Team members: Nhan Tran, JingXuan Wu, Nhan Phan.  

<b>Intro video</b>  
   
[![Watch the video](https://github.com/Usin2705/FishSauce/blob/master/DataSheet/betterThumbnail.png)](https://youtu.be/Oxn9pmZXiwQ)  

Hardware:  
Raspberry Pi3 B+ (with RPi camera module, microphone, mini speaker). Powered by power bank.  
LPC1549 LPCXpresso board (with 2 Ultrasonic Sensors, 2 Servo Motors, 2 L298N Motor Drivers, 1 HC-12 Wireless Serial Port Communication Module, 1 LED). Powered by power bank.  

4 Omni Wheels with 4 9V DC motors (with Hall Sensor), steel frames, wood frames with laser engraved (from another Metropolia school project), switches, 3D printed mount, steel hinge. Powered by 8 1.2V, 2800mAh Ni-MH batteries.  

Funduino Joystick Shield (not showed in the video) with HC-12 Wireless Serial Port Communication Module. Powered by 9V battery.  

3 ESP32 LOLIN D32 Pro V2.0.0 (not showed in the video). Intended to be used as BLE beacons for indoor positioning, but not managed to including it in the end of the course (worked but need a lot of improvements).  


<b>Voice recognition</b>  

[![Watch the video](https://img.youtube.com/vi/FwI58awtriI/hqdefault.jpg)](https://youtu.be/FwI58awtriI)  

RPi captures the voice command via microphone, save it as a "wav" file. The file then uploaded to Google Cloud, using Google Cloud Speech-to-Text to translate the voice to text strings. RPi receives the text strings from Google Cloud and processing the text string to identify the correct command. RPi reply using mini speakek, and send command to LPC1549 via Uart.  

Because the time to upload the "wav" file and then received the text string back is long (due to internet speed and Google's processing speed), we used 1 LED to indicate the robot is "thinking".  

Note: due to Google Cloud Speech-to-Text is a paid service (only free for 1,000 requests/month), a mini switch is used to toogle on/off this Voice recognition module. 

In the video you can see that Wall-F recognizes the voice command from our team member and reply back.  

<b>Voice command</b>  

[![Watch the video](https://img.youtube.com/vi/IM_iczHviLY/hqdefault.jpg)](https://youtu.be/IM_iczHviLY)  

In this video Wall-F move according to the command from user.  

We add some improvement for the speech recognition module. We hard code synonyms ("turn", "rotate") so the car can understand our intention easier. Because our English is not as good as native speak,We also added some adjustment to the module as well (Our "turn", "done" is very similar).  

In the video, you can see our team member holding a wooden board. That is to demostrate our ultrasonic sensors. We have 1 in the front, right beside the camera, and 1 in the back. If the ultrasonic sensors detect obstacle in front or back, it will block the car movement in that direction. However, you still see it can hit the wall if the angle is too low (as the waves take longer time to travel back). This is the common limitation of ultrasonic sensors. You can either add more ultrasonics sensors to the cars, or idealy buy or make a 360° ultrasonic sensors, if you want to solve this problem.  

We can also use LiDAR sensor to improve it 360° long range detection. Howver, LiDAR can't detect objects in short range so we still need to rely on Ultrasonic sensors.  

<b>Face Recognition</b>  

<img src="https://github.com/Usin2705/FishSauce/blob/master/DataSheet/sampleImage.png" width="480">

We trained our Wall-F using our team member's face and our instructor's face, so it can recognize 4 different face together. If it see a familiar face Wall-F will speak out loud his/her name.  

The Face Recognition have two steps. The first step is "Face Detection" using Haar Feature-based Cascade Classifiers. After detect all face available in the picture, in step 2, it will pass all faces image to our trained data. If the face image is similar to what we have trained it, it will "recognize" the face and output the result. Otherwise the face will be labeled as "Unknown". The key point here is to edit the "tolerance" level, high tolerance will make the model wrongly recognize unknown face as our faces, while low tolerance make it more difficult to recognized a trained face.  
   
[![Watch the video](https://img.youtube.com/vi/Zycl3cfg9Co/hqdefault.jpg)](https://youtu.be/Zycl3cfg9Co)  

In this video, aside from Face Recognition, you can also see Wall-F face tracking module. We programmed it so that it will track the face of one of our members (Nhan Phan), and will also move the camera so that his face is placed in the center of the picture. If it is tracking his face and Nhan moved out of the camera, it will move the camera around to look for him.  

<b>Face Following</b>  

[![Watch the video](https://img.youtube.com/vi/7ia6n6tgUho/hqdefault.jpg)](https://youtu.be/7ia6n6tgUho)  

Wall-F also have a different mode called "Face Following". If this mode is turn on (using voice control), it will stop all face Tracking, and move the camera upward. Upon regconized the face of our team member, it will move closer to him. Howver, in reality, the RPi camera is not good with handling ligth from lightbulbs in the celling (and we have a lot of celling lights in our school). As a result, picture took by the RPi when the camera moving up is very difficult to see, and make face recognition from those picture almost impossible.  

<b>Streaming to TV</b>  

[![Watch the video](https://img.youtube.com/vi/W5ZhVK1BvL4/hqdefault.jpg)](https://youtu.be/W5ZhVK1BvL4)  

This video is just to demostate the ability to steam the video to any IoT devices. In this case it's our smart TV. As long as they share the same network, we can log in the video feed to see real time data from Wall-F.  

Link to the LPC1549 codes, which handle the commands sent from Raspberry Pi 3, commands from HC-12 wireless module, control the motors, camera and ultrasonic sensor: https://github.com/Usin2705/FishSauce/tree/master/LPCmotor  

Link to the Raspberry Pi3 codes, which contain several sub packages (UartCommunication: Uart communication with LPC1549, camModule: handle the face regconition, speechRegModule: handle the connection with Google Cloud Service and handle the voice control from users, ttsModule: allow Wall-F to speak using a mini speaker, and textVerifyModule: utility modules help with the voice regconition): https://github.com/Usin2705/FishSauce/tree/master/RaspberryPi3. All sub packages are then grouped together and run with multiprocessing library in Python. Heavy modules (voice regconition and face regconition) are run using bash script startVoiceCam.sh, other modules is run via startMotor.sh.  

Repository also contains other features. Some which we wanted to implement but were not finished due to time constraint. BLE indoor positioning is one of those. While we managed to make it work, its accuracy did not satisfy our requirement. And we did not have time to make adjustment (or experimenting with others BLE device) to improve it.
   
<b>Schematic</b>  

[![Schematic](https://github.com/Usin2705/FishSauce/blob/master/DataSheet/Schematic.jpg)](https://github.com/Usin2705/FishSauce/blob/master/DataSheet/Wall-F_mainboard_schematic.pdf)

Actual PCB, this was done much later after our project, as our PCB machine was broken at the time. And we do not have enough budget and time for the PCB. The PCBs here are made by https://jlcpcb.com/, and they arrived near the summer of 2019.

<img src="https://github.com/Usin2705/FishSauce/blob/master/DataSheet/PCB_two_sides.jpg" width="480">

Excellent work from my teammate in designing the PCB. It has no big error when we connect all the cables, LEDs and Buttons. Our Wall-F look a lot nicer than before.

<img src="https://github.com/Usin2705/FishSauce/blob/master/DataSheet/FishSauce_and_PCB.jpg" width="480">
  

# License

Copyright 2018

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
