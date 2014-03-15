#ifndef UNITTEST_JUNITSTYLEREPORTER_H
#define UNITTEST_JUNITSTYLEREPORTER_H

#include "TestReporter.h"
#include <string>
#include <iostream>

namespace {

std::string XmlEscape(std::string const& value);
}

namespace UnitTest {


class TestDetails;

struct TestSuite
{
    std::string tests;
    std::string name;
    int testsRun;
    int testsFailed;
    float secondsElapsed;
};

class JUnitStyleReporter : public UnitTest::TestReporter
{
    public:
        /** Default constructor */
        JUnitStyleReporter(std::ostream&);
        /** Default destructor */
        ~JUnitStyleReporter();

        void ReportTestStart(TestDetails const& test);
        void ReportFailure(TestDetails const& test, char const* failure);
        void ReportTestFinish(TestDetails const& test, float secondsElapsed);
        void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);
    protected:
    private:
        void AddXmlElement(std::ostream&, char const*);
        void AddStartTag(std::ostream&);
        void AddTestSuite(std::ostream&, TestSuite);
        void AddEndTag(std::ostream&);

        TestSuite* get_suite(const char *name);

        bool m_current_failed;

        int m_num_test_suites;
        TestSuite *m_test_suites;
        TestSuite *m_current_suite;
        std::ostream &m_os;
};

} // namespace UnitTest

#endif // UNITTEST_JUNITSTYLEREPORTER_H
