#include "part.h"

using namespace MyPattern::Base;

Part::Part(Glib::ustring name, list<Point> points, list<BezierComplex> curves)
{
    //ctor
}

Part::~Part()
{
    //dtor
}

void Part::draw(shared_ptr<Cairo::Context> context)
{
    list<BezierComplex>::iterator it_curve = this->m_curves.begin();

    while(it_curve != this->m_curves.end())
    {
        it_curve->draw(context, this->is_selected(it_curve->get_name(), PARTTYPE_CURVE));
    }

    list<Point>::iterator it_point = this->m_points.begin();

    while(it_point != this->m_points.end())
    {
        it_point->draw(context, this->is_selected(it_curve->get_name(), PARTTYPE_LANDMARK));
    }
}
