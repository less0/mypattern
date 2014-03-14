#ifndef UNITTEST_JUNITSTYLEREPORTER_H
#define UNITTEST_JUNITSTYLEREPORTER_H

#include "TestReporter.h"
#include <string>

namespace UnitTest {

struct TestSuite
{
    std::string tests;
    std::string name;
    int testsRun;
    int testsFailed;

};

class JUnitStyleReporter : public UnitTest::TestReporter
{
    public:
        /** Default constructor */
        JUnitStyleReporter();
        /** Default destructor */
        ~JUnitStyleReporter();

        void ReportTestStart(TestDetails const& test);
        void ReportFailure(TestDetails const& test, char const* failure);
        void ReportTestFinish(TestDetails const& test, float secondsElapsed);
        void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);
    protected:
    private:
};

} // namespace UnitTest

#endif // UNITTEST_JUNITSTYLEREPORTER_H
