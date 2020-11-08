src = $(shell find . -name "*.cpp")
headers = $(shell find . -name "*.h")

ModuLounge: $(headers) $(src)
	g++ $(headers) $(src) -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`
