# all: %.o

OBJ=beziercomplex.o bezier.o bezierdefinition.o curvedefinition.o floatpatternparameter.o intpatternparameter.o landmark.o measures.o measurevalue.o part.o partdefinition.o pattern.o patterndefinition.o patternerror.o patternobject.o patternparameter.o patternparametervalue.o point.o test.o user.o  exception.o formulaevaluationexception.o evaluationroot.o evaluationtreenode.o evaluationtreeobserver.o constantterm.o differenceterm.o productterm.o quotientterm.o scalarterm.o sumterm.o term.o


libmypattern-base: $(OBJ)
	ar rcs libmypattern-base.a $(OBJ)

%.o: ./src/%.cpp ./src/exceptions/%.cpp ./src/evaluation/%.cpp ./src/evaluation/formula/%.cpp
	gcc -p -Wall -std=c++0x -I./include -g -c $<

clean:
	rm *.o
