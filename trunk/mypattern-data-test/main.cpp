#include <fstream>
#include <iostream>
#include "UnitTest++.h"
#include "JUnitStyleReporter.h"

using namespace std;

int main(int argc, const char* argv[])
{
    if(argc > 1 && string(argv[1]) == "junit")
    {
        ofstream os;
        os.open("test.xml");

        UnitTest::JUnitStyleReporter reporter(os);
        UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
    }

    return UnitTest::RunAllTests();
}
