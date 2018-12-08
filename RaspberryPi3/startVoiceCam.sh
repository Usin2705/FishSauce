#!/bin/bash
export WORKON_HOME=$HOME/.virtualenvs
source /usr/local/bin/virtualenvwrapper.sh
workon cv 
export DISPLAY=:0.0 
gksudo python3 VoiceCam.py