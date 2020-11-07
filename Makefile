ModuLounge: helloworld.cpp helloworld.h main.cpp
	g++ helloworld.cpp helloworld.h main.cpp -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`