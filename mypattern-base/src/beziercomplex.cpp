#include "beziercomplex.h"

#include <list>

using namespace std;
using namespace MyPattern::Base;

BezierComplex::BezierComplex(list<Bezier> bezier_curves)
{
    this->m_bezier_curves = bezier_curves;
}

BezierComplex::BezierComplex(list<Bezier> bezier_curves, string curve_name)
{
    this->m_bezier_curves = bezier_curves;
    this->m_curve_name = curve_name;
}

BezierComplex::BezierComplex()
{
}

BezierComplex::BezierComplex(const BezierComplex& bezier_complex)
{
    list<Bezier>::const_iterator it = bezier_complex.m_bezier_curves.begin();

    while(it != bezier_complex.m_bezier_curves.end())
    {
        this->m_bezier_curves.push_back(*it);
        it++;
    }

    this->m_curve_name = bezier_complex.m_curve_name;
}

double BezierComplex::get_length()
{
    list<Bezier>::iterator it = m_bezier_curves.begin();
    double sum = .0d;

    while(it != m_bezier_curves.end())
    {
        sum += (*it).get_length();
        it++;
    }

    return sum;
}

Point BezierComplex::get_coordinate(double rel_length)
{
    double length = this->get_length();

    double sum = .0d;
    list<Bezier>::iterator it = m_bezier_curves.begin();

    while(it != m_bezier_curves.end())
    {
        double current_bezier_length = (*it).get_length();

        //check if the given point lies within the current B�zier
        if((sum + current_bezier_length)/length >= rel_length)
        {
            double rel_length_bezier = (rel_length * length - sum)/current_bezier_length;
            return (*it).get_coordinate(rel_length_bezier);
        }

        sum += current_bezier_length;
        it++;
    }

    return Point(.0d, .0d);
}


string BezierComplex::get_name()
{
    return this->m_curve_name;
}

void BezierComplex::set_name(string name)
{
    this->m_curve_name = name;
}

void BezierComplex::add_bezier(Bezier curve_to_add)
{
    this->m_bezier_curves.push_back(curve_to_add);
}

double BezierComplex::get_distance(Point click)
{
    double min_distance = std::numeric_limits<double>::max();

    std::list<Bezier>::iterator it = this->m_bezier_curves.begin();

    if(it != this->m_bezier_curves.end())
    {
        if((*it).get_distance(click) < min_distance)
        {
            min_distance = (*it).get_distance(click);
        }

        it++;
    }

    return min_distance;
}

list<Bezier> BezierComplex::get_beziers()
{
	return m_bezier_curves;
}