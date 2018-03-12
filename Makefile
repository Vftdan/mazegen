windows:
	g++ -std=c++11 -static-libgcc -static-libstdc++ app.cpp -Wno-write-strings -o app.exe
	app
posix:
	g++ -std=c++11 app.cpp -Wno-write-strings -o app
	./app
