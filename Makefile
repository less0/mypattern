#
MAKEFLAGS += --no-print-directory
OUTPUT=
DEBUG?=FALSE
#CC_OPTIONS=$(shell pkg-config --cflags --libs gtkmm-3.0)

.PHONY: all coverage clean test mypattern-base mypattern-base-test mypattern-cad mypattern-data mypattern-data-test mypattern-draw mypattern-exceptions 

all: mypattern-cad

coverage: CC_OPTIONS+= --coverage
coverage: test
	@cd mypattern-base;gcov --capture --directory . --base-directory . --output-file coverage.info;genhtml coverage.info --output-directory /var/www/cov/mypattern-base

clean:
	-@make clean -C mypattern-base
	-@make clean -C mypattern-data
	-@make clean -C mypattern-draw
	-@make clean -C mypattern-cad
	-@make clean -C mypattern-base-test
	-@make clean -C mypattern-data-test
	-@make clean -C mypattern-exceptions
	-@rm -r ./cov/mypattern-base 2>/dev/null

test: mypattern-base-test mypattern-data-test

mypattern-exceptions: 
	@make -C mypattern-exceptions DEBUG=$(DEBUG)

mypattern-base: mypattern-data
	@make -C mypattern-base DEBUG=$(DEBUG)

mypattern-data: mypattern-exceptions
	@make -C mypattern-data DEBUG=$(DEBUG)

mypattern-cad: mypattern-draw
	@make -C mypattern-cad DEBUG=$(DEBUG)

mypattern-draw: mypattern-base
	@make -C mypattern-draw DEBUG=$(DEBUG)

UnitTest: 
	@make -C UnitTest++ DEBUG=$(DEBUG)

mypattern-base-test: mypattern-base UnitTest 
	@make -C mypattern-base-test DEBUG=$(DEBUG)
	@cd mypattern-base-test; ./mypattern-base-test $(OUTPUT)

mypattern-data-test: mypattern-data UnitTest
	@make -C mypattern-data-test DEBUG=$(DEBUG)
	@cd mypattern-data-test; ./mypattern-data-test $(OUTPUT)

