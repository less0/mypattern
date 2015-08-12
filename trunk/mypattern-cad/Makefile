# all: %.o

OBJ=./src/size.o ./src/patterncolumnrecord.o ./src/undocommand.o ./src/undocommandqueue.o ./src/selectnamewindow.o ./src/renamepartundocommand.o ./src/cadmainwindow.o ./src/mainwindow.o ./src/program.o
CPP=./src/size.cpp ./src/patterncolumnrecord.cpp ./src/undocommand.cpp ./src/undocommandqueue.cpp ./src/selectnamewindow.cpp ./src/renamepartundocommand.cpp ./src/cadmainwindow.cpp ./src/mainwindow.cpp ./src/program.cpp

INCLUDES=-I./include -I../mypattern-base/include/ -I../mypattern-data/include -I../mypattern-exceptions/include -I../mypattern-draw/include/ 

LIBDIRS=-L../mypattern-base/ -L../mypattern-draw/ -L../mypattern-exceptions/ -L../mypattern-data/
LIBRARIES=-lmypattern-base -lmypattern-draw -lmypattern-exceptions -lmypattern-data

OUT=mypattern-cad
CC=g++ -Wall -std=c++0x
CC_OPTIONS=$(shell pkg-config --cflags --libs gtkmm-3.0)

ifeq ($(DEBUG),TRUE)
	CC_OPTIONS+= -g
endif

mypattern-cad: message-mypattern-cad $(OBJ)
	@$(CC) $(LIBDIRS) $(INCLUDES) -o $(OUT) main.cpp $(OBJ) $(LIBRARIES) $(CC_OPTIONS)
	@cp ../GUI/mypattern-cad.glade .

message-mypattern-cad:
	@echo "\033[31mBuilding mypattern-cad\033[0m"

./src/exceptions/%.o: ./src/exceptions/%.cpp
	@$(CC) $(CC_OPTIONS)  $(INCLUDES) -o $@  -g -c $<

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base\033[0m"
	-@rm $(OUT)
	-@rm $(OBJ)
	-@rm mypattern-cad.glade
