#

all: mypattern-base

test: mypattern-base-test

mypattern-base: force-update
	cd mypattern-base; make clean; make

UnitTest: force-update
	cd UnitTest++; make

mypattern-base-test: mypattern-base UnitTest force-update
	cd mypattern-base-test; make clean; make
	./mypattern-base-test/mypattern-base-test

force-update:
	true
