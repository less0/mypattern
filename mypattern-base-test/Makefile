# all: %.o

OBJ=./src/UNT_SumTerm.o ./src/UNT_QuotientTerm.o ./src/UNT_DifferenceTerm.o ./src/INT_Formulae.o ./src/main.o ./src/UNT_Landmark.o ./src/UNT_Bezier.o ./src/UNT_ScalarTerm.o ./src/UNT_ConstantTerm.o ./src/UNT_ProductTerm.o ./src/UNT_Point.o ./src/UNT_CurveDefinition_BezierDefinition.o ./src/INT_EvaluationTree.o ./src/INT_PartDefinition.o ./src/UNT_MeasureValue.o ./src/UNT_Measures.o
# OBJ=./src/%.o

INCLUDES=-I../mypattern-base/include -I../UnitTest++/src -I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/

CC=gcc -p -Wall -std=c++0x
CC_OPTIONS=

LIBDIRS=-L../mypattern-base/ -L../UnitTest++/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/
LIBRARIES=-lUnitTest++ -lmypattern-base -lglibmm-2.4 -lsigc-2.0 -lcairomm-1.0

mypattern-base-test: message-mypattern-base-test $(OBJ)
	@g++ $(LIBDIRS) $(INCLUDES) $(CC_OPTIONS)  -o mypattern-base-test $(OBJ) -std=c++0x $(LIBRARIES)

message-mypattern-base-test:
	@echo "\033[31mBuilding mypattern-base-test\033[0m"
	

run_test: mypattern-base-test
	./mypattern-base-test


./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base-test\033[0m"
	-@rm ./mypattern-base-test 2>/dev/null
	-@rm $(OBJ) 2>/dev/null
