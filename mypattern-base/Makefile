# all: %.o

OBJ=./src/patternerror.o ./src/user.o ./src/point.o ./src/measurevalue.o ./src/curvedefinition.o ./src/floatpatternparameter.o ./src/partdefinition.o ./src/part.o ./src/pattern.o ./src/evaluation/evaluationtreeobserver.o ./src/evaluation/evaluationroot.o ./src/evaluation/evaluationtreenode.o ./src/evaluation/curveevaluationtreenode.o ./src/evaluation/formula/quotientterm.o ./src/evaluation/formula/term.o ./src/evaluation/formula/scalarterm.o ./src/evaluation/formula/constantterm.o ./src/evaluation/formula/productterm.o ./src/evaluation/formula/sumterm.o ./src/evaluation/formula/differenceterm.o ./src/patterndefinition.o ./src/intpatternparameter.o ./src/bezier.o ./src/beziercomplex.o ./src/landmark.o ./src/measures.o ./src/exceptions/formulaevaluationexception.o ./src/patternparametervalue.o ./src/patternobject.o ./src/patternparameter.o ./src/bezierdefinition.o ./src/exceptions/argumentnullexception.o ./src/exceptions/evaluationexception.o ./src/exceptions/objectnametakenevaluationexception.o ./src/evaluation/landmarkevaluationtreenode.o ./src/exceptions/unmetdependenciesevaluationexception.o ./src/exceptions/circulardependencyevaluationexception.o ./src/evaluation/measurevalueevaluationtreenode.o

#INCLUDES=-I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/
#INCLUDES=-I./include -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/lib/i386-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/cairomm-1.0/ -I/usr/include/sigc++-2.0/ -I/usr/lib/i386-linux-gnu/sigc++-2.0/include/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/cairo/ -I/usr/include/freetype2/ -I/usr/lib/i386-linux-gnu/cairomm-1.0/include/ -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include/ -I/usr/include/gtkmm-3.0/ -I/usr/include/giomm-2.4/ -I/usr/include/gdkmm-3.0/ -I/usr/lib/i386-linux-gnu/gdkmm-3.0/include/ -I/usr/lib/i386-linux-gnu/pangomm-1.4/include/ -I/usr/include/gtk-3.0/ -I/usr/include/pango-1.0/ -I/usr/include/gdk-pixbuf-2.0/ -I/usr/lib/i386-linux-gnu/gtkmm-3.0/include/ -I/usr/include/pangomm-1.4/ -I/usr/include/atkmm-1.6/ -I/usr/include/atk-1.0/
INCLUDES=-I./include -I../mypattern-exceptions/include -I../mypattern-data/include

LIB=libmypattern-base.a
CC=gcc -p -Wall -std=c++0x
CC_OPTIONS=`pkg-config --cflags --libs gtkmm-3.0`

libmypattern-base: message-libmypattern-base $(OBJ)
	@ar rcs $(LIB) $(OBJ)

message-libmypattern-base:
	@echo "\033[31mBuilding mypattern-base\033[0m"

./src/exceptions/%.o: ./src/exceptions/%.cpp
	@$(CC) $(CC_OPTIONS)  $(INCLUDES) -o $@  -g -c $<

./src/%.o: ./src/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

./src/evaluation/%.o: ./src/evaluation/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

./src/evaluation/formula/%.o: ./src/evaluation/formula/%.cpp
	@$(CC) $(CC_OPTIONS) $(INCLUDES) -o $@  -g -c $<

clean:
	@echo "\033[31mCleaning mypattern-base\033[0m"
	-@rm $(OBJ) 2>/dev/null
