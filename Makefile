src = $(shell find . -name "*.cpp")

ModuLounge: $(headers) $(src)
	g++ $(headers) $(src) -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0` -ljsoncpp -lcurl -lpthread
