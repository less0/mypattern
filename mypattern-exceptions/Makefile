# all: %.o

DEBUG?=FALSE

OBJ=./src/exception.o

INCLUDES=-I./include

LIB=libmypattern-exceptions.a
CC=gcc
CC_OPTIONS=$(shell pkg-config --cflags --libs gtkmm-3.0) -Wall -std=c++0x

ifeq ($(DEBUG),TRUE)
	CC_OPTIONS+= -g
endif

libmypattern-exceptions: message-libmypattern-exceptions $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message-libmypattern-exceptions:
	@echo "\033[31mBuilding mypattern-exceptions\033[0m"

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-exceptions\033[0m"
	rm $(OBJ)
