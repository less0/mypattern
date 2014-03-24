# all: %.o

CPP=./src/UNT_SumTerm.cpp ./src/UNT_QuotientTerm.cpp ./src/UNT_DifferenceTerm.cpp ./src/INT_Formulae.cpp ./src/main.cpp ./src/UNT_Landmark.cpp ./src/UNT_Bezier.cpp ./src/UNT_ScalarTerm.cpp ./src/UNT_ConstantTerm.cpp ./src/UNT_ProductTerm.cpp ./src/UNT_Point.cpp ./src/UNT_CurveDefinition_BezierDefinition.cpp ./src/INT_EvaluationTree.cpp 

INCLUDES=-I../mypattern-base/include -I../UnitTest++/src -I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/

LIBDIRS=-L../mypattern-base/ -L../UnitTest++/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/
LIBRARIES=-lUnitTest++ -lmypattern-base -lglibmm-2.4 -lsigc-2.0 -lcairomm-1.0

mypattern-base-test:
	g++ $(LIBDIRS) $(INCLUDES) -o mypattern-base-test $(CPP) -std=c++0x $(LIBRARIES)

%.o: %.cpp
	gcc -p -Wall -std=c++0x -I../FLAT/include -I../UnitTest++/src  -g -c $<

clean:
	rm ./mypattern-base-test
