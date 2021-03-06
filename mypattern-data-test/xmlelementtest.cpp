#include "UnitTest++.h"
#include "xmlelement.h"
#include "xmlexception.h"

#include <list>
#include <iostream>

using namespace std;
using namespace MyPattern::Data;

namespace
{
    TEST(TestXmlElementWithoutAttributes)
	{
        int end_index;
        MyPattern::Data::XmlElement::parse_element("<foo>",0,end_index);
        CHECK_EQUAL(4, end_index);
    }

    TEST(TestXmlElementEmptyAndEndElement)
	{
        int endIndex= 0;
        CHECK_THROW(XmlElement::parse_element("</foo/>", 0, endIndex), MyPattern::Data::XmlException);
    }
	
	TEST(TestCommentNode)
	{
		int endIndex = 0;
		XmlElement commentElement = XmlElement::parse_element("<!-- Comment -->",0, endIndex);
		CHECK_EQUAL(true, commentElement.isComment());
	}

    TEST(TestXmlElement)
	{
        int nextIndex = 0;
        MyPattern::Data::XmlElement element = MyPattern::Data::XmlElement::parse_element("<test int=\"1\" double=\"1.2\"><foo>", 0, nextIndex);
        CHECK_EQUAL(26, nextIndex);
        CHECK_EQUAL(false, element.isEmpty());
        CHECK_EQUAL("test", element.GetName());

        list<MyPattern::Data::XmlAttribute> parameters = element.GetAttributes();
        CHECK_EQUAL((unsigned int)2, parameters.size());
    }

    TEST(TestEmptyElement)
	{
        int nextIndex = 0;
        MyPattern::Data::XmlElement element = XmlElement::parse_element("<fooBar />", 0, nextIndex);
        CHECK_EQUAL(9, nextIndex);
        CHECK(element.isEmpty());
    }
	
	TEST(TestEmptyElementWithParameters)
	{
		int nextIndex = 0;
		XmlElement element = XmlElement::parse_element("<landmark name=\"ul\" x=\"0\" y=\"0\" />", 0, nextIndex);
		list<MyPattern::Data::XmlAttribute> parameters = element.GetAttributes();
		CHECK_EQUAL((unsigned int)3, parameters.size());
	}

    TEST(TestEndElement)
	{
        int nextIndex = 0;
        XmlElement element = XmlElement::parse_element("</fooBar>", 0, nextIndex);
        CHECK_EQUAL(8, nextIndex);
        CHECK(element.isEndElement());
    }

    TEST(TestMalformattedEndTag)
	{
        int nextIndex = 0;
        CHECK_THROW(XmlElement::parse_element("</ barfoo>", 0, nextIndex), XmlException);
    }

    TEST(TestMalformattedParameters)
	{
        int nextIndex = 0;
        CHECK_THROW(XmlElement::parse_element("<foo bar>", 0, nextIndex), XmlException);
    }
}
