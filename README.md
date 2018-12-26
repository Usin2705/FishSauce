# Wall-F
<b>IoT project 2018</b>  
Metropolia UAS, 2018.  
Team members: Nhan Tran, JingXuan Wu, Nhan Phan.  
<p>
<b>Intro video</b>  
   
[![Watch the video](https://img.youtube.com/vi/Oxn9pmZXiwQ/hqdefault.jpg)](https://youtu.be/Oxn9pmZXiwQ)  

Hardware:  
Raspberry Pi3 B+ (with RPi camera module, microphone, mini speaker). Powered by power bank.  
LPC1549 LPCXpresso board (with 2 Ultrasonic Sensors, 2 Servo Motors, 2 L298N Motor Drivers, 1 HC-12 Wireless Serial Port Communication Module, 1 LED). Powered by power bank.  
4 Omni Wheels with 4 9V DC motors (with Hall Sensor), steel frames, wood frames with laser engraved (from another Metropolia school project), switches, 3D printed mount, steel hinge. Powered by 8 1.2V, 2800mAh Ni-MH batteries.  
Funduino Joystick Shield (not showed in the video) with HC-12 Wireless Serial Port Communication Module. Powered by 9V battery.  
3 ESP32 LOLIN D32 Pro V2.0.0 (not showed in the video). Intended to be used as BLE beacons for indoor positioning, but not managed to including it in the end of the course (worked but need a lot of improvements).  

<p>  
<b>Voice recognition</b>  

[![Watch the video](https://img.youtube.com/vi/FwI58awtriI/hqdefault.jpg)](https://youtu.be/FwI58awtriI)  

RPi captures the voice command via microphone, save it as a "wav" file. The file then uploaded to Google Cloud, using Google Cloud Speech-to-Text to translate the voice to text strings. RPi receives the text strings from Google Cloud and processing the text string to identify the correct command. RPi reply using mini speakek, and send command to LPC1549 via Uart.  
Because the time to upload the "wav" file and then received the text string back is long (due to internet speed and Google's processing speed), we used 1 LED to indicate the robot is "thinking".  
In the video you can see that Wall-F recognnizes the voice command from our team member and reply back.  

<p>
<b>Voice command</b>  

[![Watch the video](https://img.youtube.com/vi/IM_iczHviLY/hqdefault.jpg)](https://youtu.be/IM_iczHviLY)  

In this video Wall-F move according to the command from user.  

<p>
<b>Face Recognition</b>  

[![Watch the video](https://img.youtube.com/vi/Zycl3cfg9Co/hqdefault.jpg)](https://youtu.be/Zycl3cfg9Co)  


<p>
<b>Face Following</b>  

[![Watch the video](https://img.youtube.com/vi/7ia6n6tgUho/hqdefault.jpg)](https://youtu.be/7ia6n6tgUho)  

<p>
<b>Streaming to TV</b>  

[![Watch the video](https://img.youtube.com/vi/W5ZhVK1BvL4/hqdefault.jpg)](https://youtu.be/W5ZhVK1BvL4)  

<p>   
   
Link to the LPC1549 codes, which handle the commands sent from Raspberry Pi 3, commands from HC-12 wireless module, control the motors, camera and ultrasonic sensor: https://github.com/Usin2705/FishSauce/tree/master/LPCmotor  
  
Link to the Raspberry Pi3 codes, which contain several sub packages (UartCommunication: Uart communication with LPC1549, camModule: handle the face regconition, speechRegModule: handle the connection with Google Cloud Service and handle the voice control from users, ttsModule: allow Wall-F to speak using a mini speaker, and textVerifyModule: utility modules help with the voice regconition): https://github.com/Usin2705/FishSauce/tree/master/RaspberryPi3. All sub packages are then grouped together and run with multiprocessing library in Python. Heavy modules (voice regconition and face regconition) are run using bash script startVoiceCam.sh, other modules is run via startMotor.sh.  
  
Repository also contains other features. Some which we wanted to implement but were not finished due to time constraint (such as BLE indoor positioning).  
   
<b>Schematic</b>  

[![Schematic](https://github.com/Usin2705/FishSauce/blob/master/DataSheet/Schematic.jpg)](https://github.com/Usin2705/FishSauce/blob/master/DataSheet/Wall-F_mainboard_schematic.pdf)

  

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
