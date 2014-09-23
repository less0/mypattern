# all: %.o

OBJ=./src/exception.o

#INCLUDES=-I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/
#INCLUDES=-I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/ -I/usr/include/gtkmm-3.0/ -I/usr/include/giomm-2.4/ -I/usr/include/gdkmm-3.0/ -I/usr/lib/i386-linux-gnu/gdkmm-3.0/include/ -I/usr/lib/i386-linux-gnu/pangomm-1.4/include/ -I/usr/include/gtk-3.0/ -I/usr/include/pango-1.0/ -I/usr/include/gdk-pixbuf-2.0/ -I/usr/lib/i386-linux-gnu/gtkmm-3.0/include/ -I/usr/include/pangomm-1.4/ -I/usr/include/atkmm-1.6/ -I/usr/include/atk-1.0/
INCLUDES=-I./include

LIB=libmypattern-exceptions.a
CC=gcc -p -Wall -std=c++0x
CC_OPTIONS=`pkg-config --cflags --libs gtkmm-3.0`

libmypattern-exceptions: message-libmypattern-exceptions $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message-libmypattern-exceptions:
	@echo "\033[31mBuilding mypattern-exceptions\033[0m"

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-exceptions\033[0m"
	-@rm $(OBJ) 2>/dev/null
