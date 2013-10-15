#include "bezier.h"


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

void Bezier::draw(shared_ptr<Cairo::Context> context)
{
    context->move_to(this->m_points[0].get_x(), this->m_points[0].get_y());
    context->curve_to(this->m_points[1].get_x(), this->m_points[1].get_y(),
                      this->m_points[2].get_x(), this->m_points[2].get_y(),
                      this->m_points[3].get_x(), this->m_points[3].get_y());

}

float Bezier::get_distance(Point click)
{
    float candidate = std::numeric_limits<float>::max();

    for(float f=0.0; f<=1.0; f+=.05)
    {
        Point p = this->get_coordinate(f);

        float dist = (p-click).abs();

        if(dist < candidate)
            candidate = dist;
    }

    return candidate;
}

Point Bezier::get_coordinate(float t)
{
    Point result(.0f,.0f);

    for(int i=0; i<4; i++)
    {
        result = result + m_points[i]*bernstein(t, i, 3);
    }

    return result;
}

float Bezier::get_length()
{
    Point last = this->get_coordinate(.0f);
    Point next;
    float dist;
    float sum;

    for(float t=.05f; t<=1.0f; t += .05f)
    {
        next = this->get_coordinate(t);

        dist = (next - last).abs();

        sum += dist;
    }

    return sum;
}

float Bezier::bernstein(float t, int i, int n)
{
    return binom(n,i)*std::pow(t, float(i))*std::pow((1.0f-t), float(n-1));
}

float Bezier::binom(int n, int k)
{
    if(k > n)
        return 0;
    else if(n==k || k==0)
        return 1;

    float binom = 1;

    for(int j=1; j<=k; j++)
    {
        binom *= float(n + 1 - j)/float(j);
    }

    return binom;
}
