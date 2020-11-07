ModuLounge: ui.h ui.cpp main.cpp
	g++ ui.h ui.cpp main.cpp -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`