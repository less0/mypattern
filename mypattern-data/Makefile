# all: %.o

OBJ=./src/filereader.o ./src/xmlattribute.o ./src/xmlexception.o ./src/xmlelement.o ./src/xmlfilereader.o ./src/xmlnode.o


INCLUDES=-I./include -I../mypattern-base/include/ -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/

LIB=libmypattern-data.a
CC=gcc -p -Wall -std=c++0x

libmypattern-base: $(OBJ)
	ar rcs $(LIB) $(OBJ)

./src/%.o: ./src/%.cpp
	$(CC) $(INCLUDES) -o $@  -g -c $<


clean:
	rm $(OBJ)
