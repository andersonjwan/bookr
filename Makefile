all:
	gcc -rdynamic `pkg-config --cflags gtk+-3.0` ./src/main.c ./src/builder.c ./src/book-add.c ./src/book-edit.c ./src/log-add.c ./src/cover-selector.c ./src/calendar-selector.c ./src/book.c ./src/log.c ./src/book-save.c ./src/book-lexer.c ./src/book-parser.c ./src/bookr-close.c ./src/bookr-open.c --output ./build/bookr.out `pkg-config --libs gtk+-3.0`
	mkdir -p /$$HOME/.local/share/bookr/data/

install:
	mkdir -p /usr/share/bookr/gui/
	cp ./src/ui/bookr.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-book-add.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-book-edit.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-log-add.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-cover-selector.ui /usr/share/bookr/gui
	cp ./src/ui/bookr-calendar-selector.ui /usr/share/bookr/gui
