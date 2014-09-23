# all: %.o

OBJ=./src/filereader.o ./src/xmlattribute.o ./src/xmlexception.o ./src/xmlelement.o ./src/xmlfilereader.o ./src/xmlnode.o
CC_OPTIONS=`pkg-config --cflags --libs gtkmm-3.0`

INCLUDES=-I./include -I../mypattern-base/include/ -I../mypattern-exceptions/include

LIB=libmypattern-data.a
CC=gcc -p -Wall $(CC_OPTIONS) -std=c++0x

libmypattern-data: message $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message:
	@echo "\033[31mBuilding mypattern-data\033[0m"

./src/%.o: ./src/%.cpp
	@$(CC) $(INCLUDES) $(CC_OPTIONS) -o $@  -g -c $<


clean:
	@echo "\033[31mCleaning mypattern-data\033[0m"
	-@rm $(OBJ) 2>/dev/null
