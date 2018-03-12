all:
	g++ -std=c++11 app.cpp -Wno-write-strings -o app
	./app
