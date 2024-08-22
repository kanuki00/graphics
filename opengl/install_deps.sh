#!/usr/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  sudo apt-get install libsdl2-dev
  sudo apt-get install libglew-dev
  sudo apt-get install libglm-dev
fi