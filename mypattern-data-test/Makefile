# all: %.o

OBJ=./xmlnodetest.o ./xmlelementtest.o ./main.o ./xmlparametertest.o
DEBUG?=FALSE

CC_OPTIONS=-Wall -std=c++0x $(shell pkg-config --cflags --libs gtkmm-3.0) 

ifeq ($(DEBUG), TRUE)
	CC_OPTIONS+= -g
endif

INCLUDES=-I../mypattern-base/include -I../mypattern-data/include -I../UnitTest++/src -I./include -I../mypattern-exceptions/include

LIBDIRS=-L../mypattern-base/ -L../mypattern-data/ -L../UnitTest++/ -L../mypattern-exceptions
LIBRARIES=-lUnitTest++ -lmypattern-data -lmypattern-base -lmypattern-exceptions

mypattern-data-test: message-mypattern-data-test $(OBJ)
	@g++ $(LIBDIRS) $(INCLUDES) $(OBJ) $(LIBRARIES) $(CC_OPTIONS) -o mypattern-data-test

message-mypattern-data-test:
	@echo "\033[31mBuilding mypattern-data-test\033[0m"

%.o: %.cpp
	@gcc $(CC_OPTIONS) -c $(INCLUDES) $<

clean:
	@echo "\033[31mCleaning mypattern-data-test\033[0m"
	-@rm ./mypattern-data-test 2>/dev/null
	-@rm ./*.o 2>/dev/null
