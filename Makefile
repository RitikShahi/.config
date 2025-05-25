all:
	g++-14 main.cpp -std=c++23 -o main \
	-I/opt/homebrew/include \
	-L/opt/homebrew/lib \
	-lraylib \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo \
	-std=c++17

run: all
	./main
