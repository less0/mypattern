#include "xmlattribute.h"
#include "UnitTest++.h"

using namespace MyPattern::Data;

namespace
{
    TEST(TestParseParameterFromTag1)
    {
        list<XmlAttribute> parameters = XmlAttribute::parse_from_tag("<a href=\"b\">");
        CHECK_EQUAL(1, parameters.size());
        list<XmlAttribute>::iterator it = parameters.begin();
        CHECK_EQUAL("href", (*it).get_name());
        CHECK_EQUAL("b", (*it).get_value());
    }

    TEST(ParseParametersFromEmptyTag)
    {
        list<XmlAttribute> parameters = XmlAttribute::parse_from_tag("<br />");
        CHECK_EQUAL(0, parameters.size());
    }

    TEST(ParseParameterWithEmptyValue)
    {
        list<XmlAttribute> parameters = XmlAttribute::parse_from_tag("<foo bar=\"\">");
        CHECK_EQUAL(1, parameters.size());
        list<XmlAttribute>::iterator it = parameters.begin();
        CHECK_EQUAL("", (*it).get_value());

    }

    TEST(MultipleParameters)
    {
        list<XmlAttribute> parameters = XmlAttribute::parse_from_tag("<foo bar=\"FOO\" foo=\"bar\" fooBAR=\"barFOO\">");
        CHECK_EQUAL(3, parameters.size());
        list<XmlAttribute>::iterator it = parameters.begin();
        CHECK_EQUAL("bar", (*it).get_name());
        CHECK_EQUAL("FOO", (*it).get_value());
        it++;
        CHECK_EQUAL("foo", (*it).get_name());
        CHECK_EQUAL("bar", (*it).get_value());
        it++;
        CHECK_EQUAL("fooBAR", (*it).get_name());
        CHECK_EQUAL("barFOO", (*it).get_value());
    }

    TEST(SelfTerminatedTags)
    {
        list<XmlAttribute> parameters = XmlAttribute::parse_from_tag("<arr foo=\"barr\"/>");
        CHECK_EQUAL(1, parameters.size());
        list<XmlAttribute>::iterator it = parameters.begin();
        CHECK_EQUAL("barr", (*it).get_value());
    }
}
