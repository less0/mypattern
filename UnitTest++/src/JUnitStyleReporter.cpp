#include "JUnitStyleReporter.h"
#include "TestDetails.h"
#include "XmlTestReporter.h"

using namespace std;

namespace {
void ReplaceChar(string& str, char c, string const& replacement)
{
    for (size_t pos = str.find(c); pos != string::npos; pos = str.find(c, pos + 1))
        str.replace(pos, 1, replacement);
}

string XmlEscape(string const& value)
{
    string escaped = value;

    ReplaceChar(escaped, '&', "&amp;");
    ReplaceChar(escaped, '<', "&lt;");
    ReplaceChar(escaped, '>', "&gt;");
    ReplaceChar(escaped, '\'', "&apos;");
    ReplaceChar(escaped, '\"', "&quot;");

    return escaped;
}
}

namespace UnitTest {

//void CStringReplace(char *str, const char* replace, const char* with)
//{
//    char* output = "";
//    char* token;
//
//    token = strtok(str, replace);
//
//    while(token != NULL)
//    {
//        strcat(output, token);
//        strcat(output, with);
//        token = strtok(NULL, replace);
//    }
//
//    int len = strlen(output);
//    memcpy(output, output, len-1);
//    output[len - 2] = '\0';
//    strcpy(str, output);
//}
//
//void XmlEscape(char* str)
//{
//    CStringReplace(str, "&", "&amp;");
//    CStringReplace(str, "<", "&lt;");
//    CStringReplace(str, ">", "&gt;");
//    CStringReplace(str, "\'", "&apos;");
//    CStringReplace(str, "\"", "&quot;");
//}

JUnitStyleReporter::JUnitStyleReporter(std::ostream& os) : m_os(os)
{
    //ctor
    m_num_test_suites = 0;
    m_test_suites = new TestSuite[0];
    m_current_failed = false;
}

JUnitStyleReporter::~JUnitStyleReporter()
{
    delete[] m_test_suites;
}

void JUnitStyleReporter::ReportTestStart(TestDetails const& details)
{
    m_current_suite = get_suite(details.suiteName);
    m_current_suite->testsRun++;

    m_current_suite->tests = m_current_suite->tests + "<testcase name=\"" + std::string(details.testName) + "\" classname=\"" + std::string(details.filename) + "\"";

    m_current_failed = false;
}

void JUnitStyleReporter::ReportFailure(TestDetails const& details, char const* failure)
{
    m_current_failed = true;
    m_current_suite->testsFailed++;

    m_current_suite->tests += ">";

    std::string failure_out = XmlEscape(std::string(failure));

    m_current_suite->tests += "<error message=\"Error in " + std::string(details.testName) + "\">" + failure_out+ "</error>";
}

void JUnitStyleReporter::ReportTestFinish(TestDetails const& details, float secondsElapsed)
{
    m_current_suite->secondsElapsed += secondsElapsed;

    if(m_current_failed)
    {
        m_current_suite->tests += "</testcase>";
    }
    else
    {
        m_current_suite->tests += " />";
    }
}

TestSuite* JUnitStyleReporter::get_suite(const char *name)
{
    for(int suite_counter = 0; suite_counter < m_num_test_suites; suite_counter++)
    {
        if(m_test_suites[suite_counter].name == std::string(name))
        {
            return &(m_test_suites[suite_counter]);
        }
    }

    TestSuite* tmp_test_suites = m_test_suites;
    m_test_suites = new TestSuite[++m_num_test_suites];

    for(int suite_counter = 0; suite_counter < m_num_test_suites-1; suite_counter++)
    {
        m_test_suites[suite_counter] = tmp_test_suites[suite_counter];
    }

    delete[] tmp_test_suites;

    m_test_suites[m_num_test_suites-1].name = std::string(name);
    m_test_suites[m_num_test_suites-1].tests = "";
    m_test_suites[m_num_test_suites-1].testsFailed = 0;
    m_test_suites[m_num_test_suites-1].testsRun = 0;

    return &(m_test_suites[m_num_test_suites-1]);
}

void JUnitStyleReporter::AddXmlElement(std::ostream& os, char const* encoding)
{
    os << "<?xml version=\"1.0\"";

    if (encoding != NULL)
        os << " encoding=\"" << encoding << "\"";

    os << "?>";
}



void JUnitStyleReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
{
    AddXmlElement(m_os, NULL);
    AddStartTag(m_os);

    for(int suite_counter = 0; suite_counter < m_num_test_suites; suite_counter++)
    {
        AddTestSuite(m_os, m_test_suites[suite_counter]);
    }

    AddEndTag(m_os);
}

void JUnitStyleReporter::AddStartTag(std::ostream &os)
{
    os << "<testsuites>" << std::endl;
}

void JUnitStyleReporter::AddTestSuite(std::ostream &os, TestSuite suite)
{
    os << "<testsuite name=\"" << suite.name << "\" tests=\"" << suite.testsRun << "\" failures=\"" << suite.testsFailed << "\">" << std::endl;

    os << suite.tests;

    os << "</testsuite>";
}

void JUnitStyleReporter::AddEndTag(std::ostream &os)
{
    os << "</testsuites>" << std::endl;
}

} // namespace UnitTest
