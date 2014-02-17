# all: %.o

OBJ=./src/user.o ./src/floatpatternparameter.o ./src/exceptions/formulaevaluationexception.o ./src/exceptions/exception.o ./src/test.o ./src/bezier.o ./src/measures.o ./src/patternparameter.o ./src/measurevalue.o ./src/evaluation/evaluationroot.o ./src/evaluation/formula/term.o ./src/evaluation/formula/differenceterm.o ./src/evaluation/formula/productterm.o ./src/evaluation/formula/scalarterm.o ./src/evaluation/formula/sumterm.o ./src/evaluation/formula/constantterm.o ./src/evaluation/formula/quotientterm.o ./src/evaluation/evaluationtreenode.o ./src/evaluation/evaluationtreeobserver.o ./src/intpatternparameter.o ./src/pattern.o ./src/bezierdefinition.o ./src/beziercomplex.o ./src/partdefinition.o ./src/patterndefinition.o ./src/point.o ./src/curvedefinition.o ./src/part.o ./src/patternerror.o ./src/patternobject.o ./src/landmark.o ./src/patternparametervalue.o
#OBJ=./src/exceptions/exception.o

lib: $(OBJ)
	ar rcs libmypattern-base.a $(OBJ)

./src/exceptions/%.o: ./src/exceptions/%.cpp
	gcc -p -Wall -std=c++0x -I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -o $@  -g -c $<

./src/%.o: ./src/%.cpp
	gcc -p -Wall -std=c++0x -I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -o $@  -g -c $<


clean:
	rm *.o
