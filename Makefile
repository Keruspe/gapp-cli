all: foobar

foobar: foobar.c
	gcc foobar.c -o foobar $(shell pkg-config --cflags --libs gtk+-3.0)

clean:
	rm -f foobar

install: all
	cp -a foobar /usr/bin/
	cp -a org.gnome.Foobar.desktop /usr/share/applications/
	cp -a org.gnome.Foobar.service /usr/share/dbus-1/services/

uninstall:
	rm -f /usr/bin/foobar /usr/share/applications/org.gnome.Foobar.desktop /usr/share/dbus-1/services/org.gnome.Foobar.service
