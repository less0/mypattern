#include "bezierdefinition.h"

#include "exceptions/argumentexception.h"

#include <sstream>
#include <iostream>

using namespace MyPattern::Base;

BezierDefinition::BezierDefinition()
{
    //ctor
}

BezierDefinition::~BezierDefinition()
{
    //dtor
}

int BezierDefinition::get_min_landmarks()
{
    return 4;
}

int BezierDefinition::get_max_landmarks()
{
    return 4;
}

BezierComplex BezierDefinition::get_bezier(list<Point> l_points)
{
    array<Point,4u> a_points;
    int index = 0;

    list<Point>::iterator it = l_points.begin();

    while(it != l_points.end() &&  index < 4)
    {
        a_points[index] = (*it);

        index++;
        it++;
    }

    list<Bezier> beziers(0);

    beziers.push_back(Bezier(a_points));

    BezierComplex bezier_complex(beziers, dynamic_cast<CurveDefinition*>(this)->get_name());

    return bezier_complex;
}

string BezierDefinition::get_class_name()
{
    return "bezier";
}

shared_ptr<CurveDefinition> BezierDefinition::deserialize_class_from_xml(shared_ptr<XmlNode> node)
{
    if(node->get_name() != "curve")
    {
		throw ArgumentException("Invalid node name");
    }
	
	shared_ptr<BezierDefinition> parsedBezierDefinition = shared_ptr<BezierDefinition>(new BezierDefinition());
	
	list<XmlAttribute> attributes = node->get_attributes();
	for(list<XmlAttribute>::iterator it = attributes.begin();
		it != attributes.end();
		it++)
	{
		if(it->get_name() == "name")
		{
			parsedBezierDefinition->set_name(it->get_value());
		}
	}
	
	list<string> landmarkNames;
	list<shared_ptr<XmlNode>> subnodes = node->get_nodes();
	
	for(list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();
		it != subnodes.end();
		it++)
	{
		if((*it)->get_name() == "lmref"
			&& (*it)->get_text() != "")
		{
			landmarkNames.push_back((*it)->get_text());
		}
	}
	parsedBezierDefinition->set_landmarks(landmarkNames);

    return parsedBezierDefinition;

}

shared_ptr<XmlNode> BezierDefinition::serialize_to_xml()
{
    return shared_ptr<XmlNode>(NULL);
}

//shared_ptr<XmlNode> BezierDefinition::get_xml()
//{
//
//    shared_ptr<XmlNode> output(new XmlNode());
//
//    output->set_name("curve");
//    output->add_parameter(XmlAttribute("type", "bezier"));
//    output->add_parameter(XmlAttribute("name", this->get_name()));
//
//
////    std::stringstream out_stream;
////
////    stringstream << "<curve type=\"bezier\" name=\"" << get_name() << "\">\r\n";
////
////    ///\todo Implement
////
////    stringstream << "</curve>";
////
////    return "";
//
//    return output;
//}
