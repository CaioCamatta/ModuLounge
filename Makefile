ModuLounge: ui.cpp ui.h main.cpp
	g++ ui.cpp ui.h main.cpp -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`