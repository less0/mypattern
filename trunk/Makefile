#
OUTPUT=junit
CC_OPTIONS=

all: mypattern-base

test: mypattern-base-test mypattern-data-test

mypattern-base: force-update
	cd mypattern-base; make CC_OPTIONS=$(CC_OPTIONS)

mypattern-data: mypattern-base
	cd mypattern-data; make CC_OPTIONS=$(CC_OPTIONS)

UnitTest: force-update
	cd UnitTest++; make

mypattern-base-test: mypattern-base UnitTest force-update
	cd mypattern-base-test; make clean; make CC_OPTIONS=$(CC_OPTIONS)
	cd mypattern-base-test; ./mypattern-base-test $(OUTPUT)

mypattern-data-test: mypattern-base mypattern-data force-update
	cd mypattern-data-test; make clean; make CC_OPTIONS=$(CC_OPTIONS)
	cd mypattern-data-test; ./mypattern-data-test $(OUTPUT)

force-update:
	true
