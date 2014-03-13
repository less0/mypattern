#include "bezierdefinition.h"

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
