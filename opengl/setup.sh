#!/usr/bin/bash

git clone git@github.com:glfw/glfw.git
git clone https://github.com/nigels-com/glew.git

sudo apt-get install libglu1-mesa-dev
sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
sudo apt install cmake

cd glew/auto
make
cd ..
make

cd ../glfw
cmake -S . -B build
cd build
make

