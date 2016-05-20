#include "UnitTest++.h"
#include "landmark.h"
#include "mypattern-base.h"

using namespace MyPattern::Base;
using namespace MyPattern::Exceptions;

namespace
{
    TEST(SetLandmarkNameTest)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new MyPattern::Base::Landmark());
        landmark->set_name("landmark123");
    }

    TEST(GetLandmarkNameTest)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("LM1");
        CHECK_EQUAL("LM1", landmark->get_name());
    }

    TEST(LandmarkDefaultValuesTest)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        CHECK_EQUAL("0", landmark->get_definition_x());
        CHECK_EQUAL("0", landmark->get_definition_y());
    }

    TEST(LandmarkGetDependencies)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("lm1");
        landmark->set_definition_x("$lm2[X]*2");
        landmark->set_definition_y("$lm2[Y]*2");

        list<string> dependencies = landmark->depends_on();

        CHECK_EQUAL((unsigned int)1, dependencies.size());

        list<string>::iterator it = dependencies.begin();
        CHECK_EQUAL("$lm2", *it);
    }

	TEST(DeserializeFromXml)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("name", "TEST"));
		landmarkNode->add_attribute(XmlAttribute("x", "1.0+2.14159"));
		landmarkNode->add_attribute(XmlAttribute("y", "-0.5+0.5"));
		
		shared_ptr<Landmark> parsedLandmark = Landmark::deserialize_from_xml(landmarkNode);
		
		CHECK_EQUAL(false, parsedLandmark == NULL);
		CHECK_EQUAL("TEST", parsedLandmark->get_name());
	}
	
	TEST(ExceptionNameEmpty)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("name", ""));
		landmarkNode->add_attribute(XmlAttribute("x", "1.0+2.14159"));
		landmarkNode->add_attribute(XmlAttribute("y", "-0.5+0.5"));
		
		CHECK_THROW(Landmark::deserialize_from_xml(landmarkNode), ArgumentException);
	}
	
	TEST(ExceptionNameMissing)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("x", "1.0+2.14159"));
		landmarkNode->add_attribute(XmlAttribute("y", "-0.5+0.5"));
		
		CHECK_THROW(Landmark::deserialize_from_xml(landmarkNode), ArgumentException);
	}
	
	TEST(DeserializeExceptionXEmpty)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("name", "TEST"));
		landmarkNode->add_attribute(XmlAttribute("x", ""));
		landmarkNode->add_attribute(XmlAttribute("y", "-0.5+0.5"));
		
		CHECK_THROW(Landmark::deserialize_from_xml(landmarkNode), ArgumentException);
	}
	
	TEST(DeserializeExceptionXMissing)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("name", "TEST"));
		landmarkNode->add_attribute(XmlAttribute("y", "-0.5+0.5"));
		
		CHECK_THROW(Landmark::deserialize_from_xml(landmarkNode), ArgumentException);
	}
	
	TEST(DeserializeExceptionYEmpty)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("name", "TEST"));
		landmarkNode->add_attribute(XmlAttribute("x", "1.0+2.14159"));
		landmarkNode->add_attribute(XmlAttribute("y", ""));
		
		CHECK_THROW(Landmark::deserialize_from_xml(landmarkNode), ArgumentException);

	}
	
	TEST(DeserializeExceptionYMissing)
	{
		shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
		landmarkNode->add_attribute(XmlAttribute("name", "TEST"));
		landmarkNode->add_attribute(XmlAttribute("x", "1.0+2.14159"));
		
		CHECK_THROW(Landmark::deserialize_from_xml(landmarkNode), ArgumentException);
	}
}
