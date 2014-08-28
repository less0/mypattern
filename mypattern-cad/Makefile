# all: %.o

OBJ=./src/size.o ./src/patterncolumnrecord.o ./src/undocommand.o ./src/undocommandqueue.o ./src/selectnamewindow.o ./src/renamepartundocommand.o ./src/cadmainwindow.o ./src/mainwindow.o ./src/program.o 
CPP=./src/size.cpp ./src/patterncolumnrecord.cpp ./src/undocommand.cpp ./src/undocommandqueue.cpp ./src/selectnamewindow.cpp ./src/renamepartundocommand.cpp ./src/cadmainwindow.cpp ./src/mainwindow.cpp ./src/program.cpp 

INCLUDES=-I./include -I../mypattern-base/include/ 

LIBDIRS=-L../mypattern-base/ -L../mypattern-draw/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/
LIBRARIES=-lmypattern-base -lmypattern-draw

OUT=libmypattern-cad
CC=g++ -p -Wall -std=c++0x
CC_OPTIONS=

mypattern-cad: message-mypattern-cad 
	@$(CC) $(CC_OPTIONS) $(LIBDIRS) $(INCLUDES) -o $(OUT) main.cpp $(CPP) $(LIBRARIES) `pkg-config --cflags --libs gtkmm-3.0`
	@cp ../GUI/mypattern-cad.glade .

message-mypattern-cad:	
	@echo "\033[31mBuilding mypattern-cad\033[0m"

./src/exceptions/%.o: ./src/exceptions/%.cpp
	@$(CC) $(CC_OPTIONS)  $(INCLUDES) -o $@  -g -c $<

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base\033[0m"
	-@rm $(OUT) 2>/dev/null
	-@rm mypattern-cad.glade 2>/dev/null 
