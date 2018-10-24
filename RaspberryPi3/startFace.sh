#!/bin/sh

#only work in cv environment
cd $HOME
. ./profile
workon cv
echo "Changed environment"

cd /home/pi/Desktop/FishSauce
echo "Navigated to the folder"

sudo python pi_face_recognition.py --cascade haarcascade_frontalface_default.xml --encodings encodings.pickle
