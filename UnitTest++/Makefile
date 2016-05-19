# all: %.o

OBJ=./src/TestResults.o ./src/Checks.o ./src/AssertException.o ./src/CurrentTest.o ./src/tests/TestCheckMacros.o ./src/tests/TestUnitTest++.o ./src/tests/TestTestMacros.o ./src/tests/TestTestSuite.o ./src/tests/TestTimeConstraintMacro.o ./src/tests/TestTestList.o ./src/tests/TestMemoryOutStream.o ./src/tests/TestTest.o ./src/tests/TestTestResults.o ./src/tests/TestCurrentTest.o ./src/tests/TestDeferredTestReporter.o ./src/tests/TestChecks.o ./src/tests/TestTestRunner.o ./src/tests/Main.o ./src/tests/TestAssertHandler.o ./src/tests/TestTimeConstraint.o ./src/tests/TestXmlTestReporter.o ./src/TimeConstraint.o ./src/ReportAssert.o ./src/TestReporter.o ./src/TestRunner.o ./src/Test.o ./src/TestList.o ./src/DeferredTestReporter.o ./src/TestReporterStdout.o ./src/DeferredTestResult.o ./src/MemoryOutStream.o ./src/XmlTestReporter.o ./src/JUnitStyleReporter.o ./src/TestDetails.o
DEBUG?=FALSE
CC=gcc
CC_OPTIONS=-Wall -std=c++0x -c

UNAME=$(shell uname)
MINGW=$(findstring MINGW,$(UNAME))

ifeq ($(MINGW),MINGW)
	OBJ+= ./src/Win32/TimeHelpers.o
else
	OBJ+= ./src/Posix/SignalTranslator.o ./src/Posix/TimeHelpers.o
endif

ifeq ($(DEBUG),TRUE)
	CC_OPTIONS+= -g
endif

lib: message-lib $(OBJ)
	@ar rcs libUnitTest++.a $(OBJ)

message-lib:
	@echo "\033[31mBuilding UnitTest++\033[0m"

./src/%.o: %.cpp
	@"$(CC)" $(CC_OPTIONS) -I./include $<
	
./src/Win32/%.o: %.cpp
	@"$(CC)" $(CC_OPTIONS)-I./include $<

./src/Posix/%.o: %.cpp
	@"$(CC)" $(CC_OPTIONS) -I./include $<

clean:
	@echo "\033[31mCleaning UnitTest++\033[0m"
	-@rm -f $(OBJ)