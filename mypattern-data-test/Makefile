# all: %.o

CPP=./xmlnodetest.cpp ./xmlelementtest.cpp ./main.cpp ./xmlparametertest.cpp

INCLUDES=-I../mypattern-base/include -I../mypattern-data/include -I../UnitTest++/src -I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/

LIBDIRS=-L../mypattern-base/ -L../mypattern-data/ -L../UnitTest++/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/
LIBRARIES=-lUnitTest++ -lmypattern-data  -lmypattern-base -lglibmm-2.4 -lsigc-2.0

mypattern-base-test:
	g++ $(LIBDIRS) $(INCLUDES) -o mypattern-data-test $(CPP) -std=c++0x $(LIBRARIES)

%.o: %.cpp
	gcc -p -Wall -std=c++0x -I../FLAT/include -I../UnitTest++/src  -g -c $<

clean:
	rm ./mypattern-base-test
