#include "part.h"

using namespace MyPattern::Base;

Part::Part(string name, list<Point> points, list<BezierComplex> curves)
{
    m_name = name;
    m_points = points;
    m_curves = curves;
}

Part::Part(const Part& base)
{
    m_name = base.m_name;
    m_points = base.m_points;
    m_curves = base.m_curves;
}

Part::~Part()
{
    //dtor
}


string Part::get_name()
{
    return m_name;
}

void Part::set_name(string name)
{
    m_name = name;
}
