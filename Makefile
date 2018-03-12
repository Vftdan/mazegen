all:
	g++ -std=c++11 -static-libgcc -static-libstdc++ app.cpp -Wno-write-strings -o app
	./app
