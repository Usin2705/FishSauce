# Wall-F
<b>IoT project 2018</b>
<p>
Metropolia UAS, 2018. 
<p>
Team members: Nhan Tran, JingXuan Wu, Nhan Phan.
<p>
<b>Intro video</b>
<p>

[![Watch the video](https://img.youtube.com/vi/Oxn9pmZXiwQ/hqdefault.jpg)](https://youtu.be/Oxn9pmZXiwQ)

<p>   
<b>Voice recognition</b>
<p>

[![Watch the video](https://img.youtube.com/vi/FwI58awtriI/hqdefault.jpg)](https://youtu.be/FwI58awtriI)

<p>
<b>Voice command</b>
<p>

[![Watch the video](https://img.youtube.com/vi/IM_iczHviLY/hqdefault.jpg)](https://youtu.be/IM_iczHviLY)

<p>
<b>Face Recognition</b>
<p>

[![Watch the video](https://img.youtube.com/vi/Zycl3cfg9Co/hqdefault.jpg)](https://youtu.be/Zycl3cfg9Co)

<p>
<b>Face Following</b>
<p>

[![Watch the video](https://img.youtube.com/vi/7ia6n6tgUho/hqdefault.jpg)](https://youtu.be/7ia6n6tgUho)

<p>
<b>Streaming to TV</b>
<p>

[![Watch the video](https://img.youtube.com/vi/W5ZhVK1BvL4/hqdefault.jpg)](https://youtu.be/W5ZhVK1BvL4)

<p>
   
   
<p>
Link to the LPC1549 codes, which handle the commands sent from Raspberry Pi 3, commands from HC-12 wireless module, control the motors, camera and ultrasonic sensor: https://github.com/Usin2705/FishSauce/tree/master/LPCmotor
<p>
Link to the Raspberry Pi3 codes, which contain several sub packages (UartCommunication: Uart communication with LPC1549, camModule: handle the face regconition, speechRegModule: handle the connection with Google Cloud Service and handle the voice control from users, ttsModule: allow Wall-F to speak using a mini speaker, and textVerifyModule: utility modules help with the voice regconition): https://github.com/Usin2705/FishSauce/tree/master/RaspberryPi3. All sub packages are then grouped together and run with multiprocessing library in Python. Heavy modules (voice regconition and face regconition) are run using bash script startVoiceCam.sh, other modules is run via startMotor.sh.
<p>
Repository also contains other features. Some which we wanted to implement but were not finished due to time constraint (such as BLE indoor positioning).
   
<b>Schematic</b>
<p>

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
