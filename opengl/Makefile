TO_LINK = glew/lib/libGLEW.a glfw/build/src/libglfw3.a -lGL

all: final

final: main.o
	g++ -o program main.o $(TO_LINK)

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm main.o program
