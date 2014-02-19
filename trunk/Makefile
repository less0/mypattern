#

all: mypattern-base

test: mypattern-base-test mypattern-data-test

mypattern-base: force-update
	cd mypattern-base; make clean; make

mypattern-data: mypattern-base
	cd mypattern-data; make clean; make

UnitTest: force-update
	cd UnitTest++; make

mypattern-base-test: mypattern-base UnitTest force-update
	cd mypattern-base-test; make clean; make
	./mypattern-base-test/mypattern-base-test

mypattern-data-test: mypattern-base mypattern-data force-update
	cd mypattern-data-test; make clean; make
	./mypattern-data-test/mypattern-data-test

force-update:
	true
