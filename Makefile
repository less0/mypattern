#
MAKEFLAGS += --no-print-directory
OUTPUT=junit
CC_OPTIONS=`pkg-config --cflags --libs gtkmm-3.0`

all: mypattern-base

coverage: CC_OPTIONS=$(CC_OPTIONS) --coverage
coverage: test
	@cd mypattern-base;lcov --capture --directory . --base-directory . --output-file coverage.info;genhtml coverage.info --output-directory /var/www/cov/mypattern-base

clean:
	-@cd mypattern-base; make clean
	-@cd mypattern-data; make clean
	-@cd mypattern-draw; make clean
	-@cd mypattern-cad; make clean
	-@cd mypattern-base-test; make clean
	-@cd mypattern-data-test; make clean
	-@rm -r /var/www/cov/mypattern-base 2>/dev/null

test: mypattern-base-test mypattern-data-test

mypattern-base: force-update
	@cd mypattern-base; make CC_OPTIONS='$(CC_OPTIONS)'

mypattern-data: mypattern-base
	@cd mypattern-data; make CC_OPTIONS='$(CC_OPTIONS)'

mypattern-cad: mypattern-draw
	@cd mypattern-cad; make CC_OPTIONS='$(CC_OPTIONS)'

mypattern-draw: mypattern-base
	@cd mypattern-draw; make CC_OPTIONS='$(CC_OPTIONS)'

UnitTest: force-update
	@cd UnitTest++; make

mypattern-base-test: mypattern-base UnitTest force-update
	@cd mypattern-base-test; make CC_OPTIONS='$(CC_OPTIONS)'
	@cd mypattern-base-test; ./mypattern-base-test $(OUTPUT)

mypattern-data-test: mypattern-base mypattern-data force-update
	@cd mypattern-data-test; make CC_OPTIONS='$(CC_OPTIONS)'
	@cd mypattern-data-test; ./mypattern-data-test $(OUTPUT)

force-update:
	-@true
