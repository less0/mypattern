# all: %.o

OBJ=./src/TestResults.o ./src/Checks.o ./src/AssertException.o ./src/CurrentTest.o ./src/tests/TestCheckMacros.o ./src/tests/TestUnitTest++.o ./src/tests/TestTestMacros.o ./src/tests/TestTestSuite.o ./src/tests/TestTimeConstraintMacro.o ./src/tests/TestTestList.o ./src/tests/TestMemoryOutStream.o ./src/tests/TestTest.o ./src/tests/TestTestResults.o ./src/tests/TestCurrentTest.o ./src/tests/TestDeferredTestReporter.o ./src/tests/TestChecks.o ./src/tests/TestTestRunner.o ./src/tests/Main.o ./src/tests/TestAssertHandler.o ./src/tests/TestTimeConstraint.o ./src/tests/TestXmlTestReporter.o ./src/TimeConstraint.o ./src/Posix/SignalTranslator.o ./src/Posix/TimeHelpers.o ./src/ReportAssert.o ./src/TestReporter.o ./src/TestRunner.o ./src/Test.o ./src/TestList.o ./src/DeferredTestReporter.o ./src/TestReporterStdout.o ./src/DeferredTestResult.o ./src/MemoryOutStream.o ./src/XmlTestReporter.o ./src/TestDetails.o


lib: $(OBJ)
	ar rcs libUnitTest++.a $(OBJ)

./src/%.o: %.cpp
	gcc -p -Wall -std=c++0x -I./include  -g -c $<

./src/Posix/%.o: %.cpp
	gcc -p -Wall -std=c++0x -I./include  -g -c $<

clean:
	rm *.o
