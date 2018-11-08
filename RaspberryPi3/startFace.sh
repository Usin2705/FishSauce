#!/bin/bash

#only work in cv environment
cd $HOME
source ~/.profile
source /usr/local/bin/virtualenvwrapper.sh
workon cv
echo "Changed environment"

cd /home/pi/Desktop/FishSauce
echo "Navigated to the folder"

#sudo python3 pi_face_recognition.py --cascade haarcascade_frontalface_default.xml --encodings encodings.pickle
