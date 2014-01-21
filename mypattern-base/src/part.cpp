#include "part.h"

using namespace MyPattern::Base;

Part::Part(Glib::ustring name, list<Point> points, list<BezierComplex> curves)
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

//void Part::draw(shared_ptr<Cairo::Context> context)
//{
////    list<BezierComplex>::iterator it_curve = this->m_curves.begin();
////
////    while(it_curve != this->m_curves.end())
////    {
////        it_curve->draw(context, this->is_selected(it_curve->get_name(), PARTTYPE_CURVE));
////    }
////
////    list<Point>::iterator it_point = this->m_points.begin();
////
////    while(it_point != this->m_points.end())
////    {
////        it_point->draw(context, this->is_selected(it_curve->get_name(), PARTTYPE_LANDMARK));
////    }
//}

Glib::ustring Part::get_name()
{
    return m_name;
}

void Part::set_name(Glib::ustring name)
{
    m_name = name;
}
