all:
	gcc -rdynamic `pkg-config --cflags gtk+-3.0` ./src/bookr-main.c ./src/bookr-builder.c ./src/bookr-book-add.c ./src/bookr-book-edit.c ./src/bookr-log-add.c ./src/bookr-cover-selector.c ./src/bookr-calendar-selector.c ./src/bookr-book-selector.c ./src/bookr-book.c ./src/bookr-log.c ./src/bookr-book-save.c ./src/bookr-book-lexer.c ./src/bookr-book-parser.c ./src/bookr-close.c ./src/bookr-open.c ./src/bookr-time.c ./src/bookr-calendar.c ./src/bookr-stack.c ./src/bookr-stats.c --output ./build/bookr `pkg-config --libs gtk+-3.0`
	mkdir -p /$$HOME/.local/share/bookr/data/

install:
	mkdir -p /usr/share/bookr/gui/
	cp ./src/ui/bookr.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-book-add.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-book-edit.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-log-add.ui /usr/share/bookr/gui/
	cp ./src/ui/bookr-cover-selector.ui /usr/share/bookr/gui
	cp ./src/ui/bookr-calendar-selector.ui /usr/share/bookr/gui
	cp ./src/ui/bookr-book-selector.ui /usr/share/bookr/gui
	cp ./data/covers/default-cover.jpg /usr/share/bookr/gui

	install -Dm644 ./data/icons/hicolor/48x48/com.github.andersonjwan.bookr.png -t /usr/share/icons/hicolor/48x48/apps/
	install -Dm644 ./data/icons/hicolor/64x64/com.github.andersonjwan.bookr.png  -t/usr/share/icons/hicolor/64x64/apps/
	install -Dm644 ./data/icons/hicolor/128x128/com.github.andersonjwan.bookr.png -t /usr/share/icons/hicolor/128x128/apps/
	install -Dm644 ./data/icons/hicolor/256x256/com.github.andersonjwan.bookr.png -t /usr/share/icons/hicolor/256x256/apps/
	install -Dm644 ./data/icons/hicolor/512x512/com.github.andersonjwan.bookr.png -t /usr/share/icons/hicolor/512x512/apps/
	install -Dm644 ./data/icons/hicolor/scalable/com.github.andersonjwan.bookr.svg -t /usr/share/icons/hicolor/scalable/apps/
	install -Dm644 ./data/com.github.andersonjwan.bookr.desktop -t /usr/share/applications/

	gtk-update-icon-cache -t /usr/share/icons/hicolor/
	update-desktop-database
	install -Dm777 ./build/bookr /usr/local/bin/
