# all: %.o

OBJ=./src/size.o ./src/patterncolumnrecord.o ./src/undocommand.o ./src/undocommandqueue.o ./src/selectnamewindow.o ./src/renamepartundocommand.o ./src/cadmainwindow.o ./src/mainwindow.o ./src/program.o 
CPP=./src/size.cpp ./src/patterncolumnrecord.cpp ./src/undocommand.cpp ./src/undocommandqueue.cpp ./src/selectnamewindow.cpp ./src/renamepartundocommand.cpp ./src/cadmainwindow.cpp ./src/mainwindow.cpp ./src/program.cpp 
#OBJ=./src/selectnamewindow.o ./src/cadmainwindow.o ./src/mainwindow.o ./src/program.o 

#INCLUDES=-I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/ -I/usr/include/gtkmm-3.0/ -I/usr/include/giomm-2.4/ -I/usr/include/gdkmm-3.0/ -I/usr/lib/i386-linux-gnu/gdkmm-3.0/include/ -I/usr/lib/i386-linux-gnu/pangomm-1.4/include/ -I/usr/include/gtk-3.0/ -I/usr/include/pango-1.0/ -I/usr/include/gdk-pixbuf-2.0/ -I/usr/lib/i386-linux-gnu/gtkmm-3.0/include/ -I/usr/include/pangomm-1.4/ -I/usr/include/atkmm-1.6/ -I/usr/include/atk-1.0/ -I../mypattern-base/include/ 
INCLUDES=-I./include -I../mypattern-base/include/ 

LIBDIRS=-L../mypattern-base/ -L../mypattern-draw/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/
# LIBRARIES=-lmypattern-base -lmypattern-draw -lglibmm-2.4 -lsigc-2.0 -lcairomm-1.0 -lpango-1.0 -latk-1.0 -lgdk_pixbuf-2.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -lglade-2.0 -lxml2 -lgtkmm-3.0 -lgdkmm-2.4 -latkmm-1.6 -lpangomm-1.4 -lglibmm-2.4 -lsigc-2.0 -lcairo -lz 
LIBRARIES=-lmypattern-base -lmypattern-draw

OUT=libmypattern-cad
CC=g++ -p -Wall -std=c++0x
CC_OPTIONS=

mypattern-cad: message-mypattern-cad 
	#$(CC) $(CC_OPTIONS) $(LIBDIRS) $(INCLUDES) -o $(OUT) main.cpp $(CPP) $(LIBRARIES)
	$(CC) $(CC_OPTIONS) $(LIBDIRS) $(INCLUDES) -o $(OUT) main.cpp $(CPP) $(LIBRARIES) `pkg-config --cflags --libs gtkmm-3.0`
	cp ../GUI/mypattern-cad.glade .

message-mypattern-cad:	
	@echo "\033[31mBuilding mypattern-cad\033[0m"

./src/exceptions/%.o: ./src/exceptions/%.cpp
	@$(CC) $(CC_OPTIONS)  $(INCLUDES) -o $@  -g -c $<

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base\033[0m"
	#-@rm $(OBJ) 2>/dev/null
	-@rm $(OUT) 2>/dev/null
	-@rm mypattern-cad.glade 2>/dev/null 
