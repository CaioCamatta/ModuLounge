ModuLounge: module.h module.cpp sampleModule.h sampleModule.cpp main.cpp
	g++ module.h module.cpp sampleModule.h sampleModule.cpp main.cpp -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`