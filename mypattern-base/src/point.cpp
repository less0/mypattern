#include "point.h"
#include <cmath>

using namespace MyPattern::Base;

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

Point::Point(const Point& pt)
{
    this->m_x = pt.m_x;
    this->m_y = pt.m_y;
    this->m_landmark_name = pt.m_landmark_name;
}

Point::Point()
{
    m_x = .0f;
    m_y = .0f;
}

void Point::set_x(double x)
{
    m_x = x;
}

void Point::set_y(double y)
{
    m_y = y;
}

void Point::set_landmark_name(string nameToSet)
{
	m_landmark_name = nameToSet;
}

double Point::get_x()
{
    return m_x;
}

double Point::get_y()
{
    return m_y;
}

string Point::get_landmark_name()
{
	return m_landmark_name;
}

double Point::abs()
{
    return sqrtf(this->m_x * this->m_x + this->m_y * this->m_y);
}

Point Point::operator+(const Point& summand)
{
    Point p(.0f,.0f);

    p.m_x = this->m_x + summand.m_x;
    p.m_y = this->m_y + summand.m_y;

    return p;
}

Point Point::operator-(const Point& subtrahend)
{
    Point p(.0f, .0f);

    p.m_x = this->m_x - subtrahend.m_x;
    p.m_y = this->m_y - subtrahend.m_y;
    p.m_landmark_name = "";

    return p;
}

Point Point::operator*(const double& factor)
{
    return Point(this->m_x * factor, this->m_y * factor);
}

Point Point::operator/(const double& divisor)
{
    return Point(this->m_x/divisor, this->m_y/divisor);
}

