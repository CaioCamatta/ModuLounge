src = $(shell find . -name "*.cpp")

ModuLounge: $(headers) $(src)
	g++ -std=c++11 -ljsoncpp -lcurl $(headers) $(src) -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`
