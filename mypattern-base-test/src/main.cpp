#include <iostream>
#include <fstream>
#include <limits>

#include <landmark.h>
#include "UnitTest++.h"
#include "XmlTestReporter.h"
#include "JUnitStyleReporter.h"
//#include "xmlnode.h"

//void node_out(shared_ptr<XmlNode>, int);
using namespace MyPattern::Base;

int main(int argc, const char* argv[])
{
    if(argc > 1 && string(argv[1]) == "junit")
    {
        ofstream os;
        os.open("test.xml");

        UnitTest::JUnitStyleReporter reporter(os);
        UnitTest::TestRunner runner(reporter);
        runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
	return 0;
    }

    return UnitTest::RunAllTests();
}
