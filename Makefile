all:
	gcc `pkg-config --cflags gtk+-3.0` ./src/main.c --output ./build/bookr.out `pkg-config --libs gtk+-3.0`
