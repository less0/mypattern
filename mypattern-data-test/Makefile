# all: %.o

CPP=./xmlnodetest.cpp ./xmlelementtest.cpp ./main.cpp ./xmlparametertest.cpp

CC_OPTIONS=`pkg-config --cflags --libs gtkmm-3.0`

INCLUDES=-I../mypattern-base/include -I../mypattern-data/include -I../UnitTest++/src -I./include -I../mypattern-exceptions/include

LIBDIRS=-L../mypattern-base/ -L../mypattern-data/ -L../UnitTest++/ -L../mypattern-exceptions
LIBRARIES=-lUnitTest++ -lmypattern-data  -lmypattern-base -lmypattern-exceptions -lglibmm-2.4 -lsigc-2.0

mypattern-data-test: message-mypattern-data-test
	@g++ $(LIBDIRS) $(INCLUDES) -o mypattern-data-test $(CPP) -std=c++0x  $(LIBRARIES) $(CC_OPTIONS)

message-mypattern-data-test:
	@echo "\033[31mBuilding mypattern-data-test\033[0m"

%.o: %.cpp
	@gcc -p -Wall -std=c++0x $(CC_OPTIONS)  -I../FLAT/include -I../UnitTest++/src  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-data-test\033[0m"
	-@rm ./mypattern-data-test 2>/dev/null
