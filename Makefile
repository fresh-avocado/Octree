all:
	clear && g++ -std=c++17 main.cpp -I /opt/X11/include -L /opt/X11/lib -lX11 -ljpeg -lz -pthread

clean:
	rm a.out
	rm -rf a.out.dSYM