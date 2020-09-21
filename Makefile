all:
	gcc `pkg-config --cflags gtk+-3.0` ./src/main.c ./src/builder.c --output ./build/bookr.out `pkg-config --libs gtk+-3.0`

install:
	mkdir -p /usr/share/bookr/gui/
	cp ./src/ui/bookr.ui /usr/share/bookr/gui/
