# all: %.o

OBJ=./src/patternerror.o ./src/user.o ./src/point.o ./src/measurevalue.o ./src/curvedefinition.o ./src/floatpatternparameter.o ./src/partdefinition.o ./src/part.o ./src/pattern.o ./src/evaluation/evaluationtreeobserver.o ./src/evaluation/evaluationroot.o ./src/evaluation/evaluationtreenode.o ./src/evaluation/curveevaluationtreenode.o ./src/evaluation/formula/quotientterm.o ./src/evaluation/formula/term.o ./src/evaluation/formula/scalarterm.o ./src/evaluation/formula/constantterm.o ./src/evaluation/formula/productterm.o ./src/evaluation/formula/sumterm.o ./src/evaluation/formula/differenceterm.o ./src/patterndefinition.o ./src/intpatternparameter.o ./src/bezier.o ./src/beziercomplex.o ./src/landmark.o ./src/measures.o ./src/exceptions/formulaevaluationexception.o ./src/patternparametervalue.o ./src/patternobject.o ./src/patternparameter.o ./src/bezierdefinition.o ./src/exceptions/argumentnullexception.o ./src/exceptions/argumentexception.o ./src/exceptions/evaluationexception.o ./src/exceptions/objectnametakenevaluationexception.o ./src/evaluation/landmarkevaluationtreenode.o ./src/exceptions/unmetdependenciesevaluationexception.o ./src/exceptions/circulardependencyevaluationexception.o ./src/evaluation/measurevalueevaluationtreenode.o

INCLUDES=-I./include -I../mypattern-exceptions/include -I../mypattern-data/include

LIB=libmypattern-base.a
CC=gcc
CC_OPTIONS=$(shell pkg-config --cflags --libs gtkmm-3.0) -Wall -std=c++0x

libmypattern-base: message-libmypattern-base $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message-libmypattern-base:
	@echo "\033[31mBuilding mypattern-base\033[0m"

./src/exceptions/%.o: ./src/exceptions/%.cpp
	@"$(CC)" $(CC_OPTIONS) $(INCLUDES) -o $@ -g -c $<

./src/%.o: ./src/%.cpp
	@"$(CC)" $(CC_OPTIONS) $(INCLUDES) -o $@ -g -c $<

./src/evaluation/%.o: ./src/evaluation/%.cpp
	@"$(CC)" $(CC_OPTIONS) $(INCLUDES) -o $@ -g -c $<

./src/evaluation/formula/%.o: ./src/evaluation/formula/%.cpp
	@"$(CC)" $(CC_OPTIONS) $(INCLUDES) -o $@ -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base\033[0m"
	-@rm $(OBJ)
