# all: %.o

OBJ=./src/patterndrawer.o ./src/papersettings.o ./src/drawoptions.o ./src/exceptions/pageoutofrangeexception.o ./src/cairopatterndrawer.o 

INCLUDES=-I./include -I../mypattern-base/include -I../mypattern-base/include/exceptions

LIB=libmypattern-draw.a
CC=gcc -Wall -std=c++0x
CC_OPTIONS=$(shell pkg-config --cflags --libs gtkmm-3.0)

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
	-@rm $(OBJ)
