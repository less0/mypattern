# all: %.o

OBJ=./src/patterndrawer.o ./src/papersettings.o ./src/drawoptions.o ./src/exceptions/pageoutofrangeexception.o ./src/cairopatterndrawer.o 

INCLUDES=-I./include -I../mypattern-base/include -I../mypattern-base/include/exceptions -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/

LIB=libmypattern-draw.a
CC=gcc -p -Wall -std=c++0x
CC_OPTIONS=

libmypattern-draw: message-libmypattern-draw $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message-libmypattern-draw:	
	@echo "\033[31mBuilding mypattern-draw\033[0m"

./src/exceptions/%.o: ./src/exceptions/%.cpp
	@$(CC) $(CC_OPTIONS)  $(INCLUDES) -o $@  -g -c $<

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-draw\033[0m"
	-@rm $(OBJ) 2>/dev/null
