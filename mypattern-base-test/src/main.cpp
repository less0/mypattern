#include <iostream>
#include <limits>

#include <landmark.h>
#include "UnitTest++.h"
#include "XmlTestReporter.h"
#include "JUnitStyleReporter.h"
//#include "xmlnode.h"

//void node_out(shared_ptr<XmlNode>, int);
using namespace MyPattern::Base;

int main()
{
//    UnitTest::JUnitStyleReporter reporter(std::cerr);
//	UnitTest::TestRunner runner(reporter);
//	return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);

    return UnitTest::RunAllTests();
}
