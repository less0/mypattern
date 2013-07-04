#include "bezierdefinition.h"

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

    ///\todo check how the object casts work and then cast this to CurveDefinition to get the name
    BezierComplex bezier_complex(beziers, dynamic_cast<CurveDefinition*>(this)->get_name());

    return bezier_complex;
}

ustring BezierDefinition::get_xml()
{
    ///\todo Implement
    return "";
}
