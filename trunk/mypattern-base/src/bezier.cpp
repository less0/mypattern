#include "bezier.h"
#include <iostream>

using namespace MyPattern::Base;

Bezier::Bezier(array<Point,4> points)
{
    m_points = points;
}

Bezier::Bezier(const Bezier& bezier)
{
    for(int pt_index = 0; pt_index < 4; pt_index++)
    {
        this->m_points[pt_index] = Point(bezier.m_points[pt_index]);
    }
}

Bezier::Bezier()
{}

void Bezier::draw(shared_ptr<Cairo::Context> context)
{
    context->move_to(this->m_points[0].get_x(), this->m_points[0].get_y());
    context->curve_to(this->m_points[1].get_x(), this->m_points[1].get_y(),
                      this->m_points[2].get_x(), this->m_points[2].get_y(),
                      this->m_points[3].get_x(), this->m_points[3].get_y());

}

double Bezier::get_distance(Point click)
{
    double candidate = std::numeric_limits<double>::max();

    for(double f=0.0; f<=1.0; f+=.05)
    {
        Point p = this->get_coordinate(f);

        double dist = (p-click).abs();

        if(dist < candidate)
            candidate = dist;
    }

    return candidate;
}

Point Bezier::get_coordinate(double t)
{
    Point result(.0f,.0f);

    for(int i=0; i<4; i++)
    {
        result = result + m_points[i]*bernstein(t, i, 3);
    }

    return result;
}

double Bezier::get_length()
{
    Point last = this->get_coordinate(.0d);
    Point next;
    double dist;
    double sum = 0;

    for(double t=.05d; t<=1.0d; t += .05d)
    {
        next = this->get_coordinate(t);

        dist = (next - last).abs();

        sum += dist;
    }

    return sum;
}

double Bezier::bernstein(double t, int i, int n)
{
    if(i == n)
    {
        return binom(n,i)*std::pow(t, double(i));
    }
    else if(i == 0)
    {
        return binom(n,i)*std::pow((1.0d-t), double(n-i));
    }

    return binom(n,i)*std::pow(t, double(i))*std::pow((1.0d-t), double(n-i));
}

double Bezier::binom(int n, int k)
{
    if(k > n)
        return 0;
    else if(n==k || k==0)
        return 1;

    double binom = 1;

    for(int j=1; j<=k; j++)
    {
        binom *= double(n + 1 - j)/double(j);
    }

    return binom;
}


