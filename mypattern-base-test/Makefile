# all: %.o

OBJ=./src/UNT_SumTerm.o ./src/UNT_QuotientTerm.o ./src/UNT_DifferenceTerm.o ./src/INT_Formulae.o ./src/main.o ./src/UNT_Landmark.o ./src/UNT_Bezier.o ./src/UNT_ScalarTerm.o ./src/UNT_ConstantTerm.o ./src/UNT_ProductTerm.o ./src/UNT_Point.o ./src/UNT_CurveDefinition.o ./src/UNT_CurveDefinition_BezierDefinition.o ./src/INT_EvaluationTree.o ./src/INT_PartDefinition.o ./src/UNT_MeasureValue.o ./src/UNT_Measures.o ./src/UNT_Exception.o ./src/UNT_FormulaEvaluationException.o
# OBJ=./src/%.o

INCLUDES=-I../mypattern-base/include -I../UnitTest++/src -I./include -I../mypattern-exceptions/include -I../mypattern-data/include

CC=gcc
CC_OPTIONS=$(shell pkg-config --cflags --libs gtkmm-3.0) -Wall -std=c++0x

LIBDIRS=-L../mypattern-base/ -L../UnitTest++/ -L../mypattern-exceptions/ -L../mypattern-data/
LIBRARIES=-lUnitTest++ -lmypattern-base -lmypattern-exceptions -lmypattern-data

mypattern-base-test: message-mypattern-base-test $(OBJ)
	@g++ $(LIBDIRS) $(INCLUDES) -o mypattern-base-test $(OBJ) -std=c++0x $(LIBRARIES) $(CC_OPTIONS) 

message-mypattern-base-test:
	@echo "\033[31mBuilding mypattern-base-test\033[0m"


run_test: mypattern-base-test
	./mypattern-base-test


./src/%.o: ./src/%.cpp
	@"$(CC)" $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base-test\033[0m"
	-@rm ./mypattern-base-test 2>/dev/null
	-@rm $(OBJ) 2>/dev/null
