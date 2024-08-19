#!/usr/bin/bash

if [ ! -d "glfw" ] | [ ! -d "glew" ] | [ ! -d "json" ] | [ ! -d "glm" ]; then
	if [[ "$OSTYPE" == "linux-gnu"* ]]; then
		git clone git@github.com:glfw/glfw.git
		git clone git@github.com:nigels-com/glew.git
		git clone git@github.com:nlohmann/json.git
		git clone git@github.com:g-truc/glm.git

		sudo apt-get install libglu1-mesa-dev
		sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev
		sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
		sudo apt install cmake

		cd glew/auto
		make
		cd ..
		make
    cd ..

    if [ ! -d "glfw/build" ]; then
      cd glfw
      cmake -S . -B build
      cd build
      make
    fi

	elif [[ "$OSTYPE" == "msys" ]]; then
	  git clone https://github.com/glfw/glfw.git
		git clone https://github.com/nigels-com/glew.git
		git clone https://github.com/nlohmann/json.git
		git clone https://github.com/g-truc/glm.git
	fi
fi
