#include "UnitTest++.h"
#include "mypattern-base.h"
#include "exceptions/argumentexception.h"

#include <iostream>

using namespace MyPattern::Base;
using namespace MyPattern::Exceptions;

namespace
{
	

    TEST(TestRegisterClasses)
    {
        shared_ptr<CurveDefinition> bezier_prototype = shared_ptr<CurveDefinition>(new BezierDefinition());

        CurveDefinition::register_class(bezier_prototype);
        list<ustring> class_names = CurveDefinition::get_registered_class_names();
        CHECK_EQUAL(1, class_names.size());
		list<ustring>::iterator it = class_names.begin();
		CHECK_EQUAL("bezier", *it);
    }

	TEST(DeserializeFromXml)
	{
		
			// shared_ptr<CurveDefinition> bezier_prototype = shared_ptr<CurveDefinition>(new BezierDefinition());
			// CurveDefinition::register_class(bezier_prototype);
			
			shared_ptr<XmlNode> curveNode = shared_ptr<XmlNode>(new XmlNode("curve"));
			curveNode->add_attribute(XmlAttribute("name", "FooBar"));
			curveNode->add_attribute(XmlAttribute("type", "bezier"));
			
			shared_ptr<XmlNode> pointNode = shared_ptr<XmlNode>(new XmlNode("lmref"));
			pointNode->set_text("A");
			curveNode->add_node(pointNode);
			
			pointNode = shared_ptr<XmlNode>(new XmlNode("lmref"));
			pointNode->set_text("B");
			curveNode->add_node(pointNode);
			
			pointNode = shared_ptr<XmlNode>(new XmlNode("lmref"));
			pointNode->set_text("C");
			curveNode->add_node(pointNode);
			
			pointNode = shared_ptr<XmlNode>(new XmlNode("lmref"));
			pointNode->set_text("D");
			curveNode->add_node(pointNode);
			
			shared_ptr<CurveDefinition> deserializedCurveDefinition = CurveDefinition::deserialize_from_xml(curveNode);
			
			CHECK_EQUAL(false, deserializedCurveDefinition == NULL);
			
			if(deserializedCurveDefinition != NULL)
			{
				CHECK_EQUAL("bezier", deserializedCurveDefinition->get_class_name());
				CHECK_EQUAL("FooBar", deserializedCurveDefinition->get_name());
				
				list<ustring> landmarkNames = deserializedCurveDefinition->get_landmarks();
				list<ustring>::iterator landmarkIterator = landmarkNames.begin();
				CHECK_EQUAL("A", *landmarkIterator);
				landmarkIterator++;
				CHECK_EQUAL("B", *landmarkIterator);
				landmarkIterator++;
				CHECK_EQUAL("C", *landmarkIterator);
				landmarkIterator++;
				CHECK_EQUAL("D", *landmarkIterator);
			}

			
	}
}
