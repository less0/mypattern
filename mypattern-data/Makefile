# all: %.o

OBJ=./src/filereader.o ./src/xmlattribute.o ./src/xmlexception.o ./src/xmlelement.o ./src/xmlfilereader.o ./src/xmlnode.o ./src/exceptions/filenotfoundexception.o
CC_OPTIONS=-Wall -std=c++0x

INCLUDES=-I./include -I../mypattern-base/include/ -I../mypattern-exceptions/include

LIB=libmypattern-data.a
CC=gcc

libmypattern-data: message $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message:
	@echo "\033[31mBuilding mypattern-data\033[0m"

./src/%.o: ./src/%.cpp
	@"$(CC)" $(INCLUDES) $(CC_OPTIONS) -o $@  -g -c $<


clean:
	@echo "\033[31mCleaning mypattern-data\033[0m"
	-@rm $(OBJ)
