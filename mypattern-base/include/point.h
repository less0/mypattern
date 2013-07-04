#ifndef POINT_H
#define POINT_H

#include "glibmm/ustring.h"
#include "cairomm/context.h"
#include <memory>

using namespace std;

/*! \brief Class representing coordinates on a plane
*/
class Point
{
    public:
        /*! \brief Creates a new Point with given values for the x- and y-component
        */
        Point(float x, float y);
        /*! \brief Creates a copy of an existing Point object
        */
        Point(const Point& pt);
        /*! \brief Creatres a new Point object with both the x- and the y-value being 0.0
        */
        Point();
        /*! \brief Sets the x-coordinate of the point
        */
        void set_x(float x);
        /*! \brief Gets the x-coordinate of the point
        */
        float get_x();
        /*! \brief Sets the y-coordinate of the point
        */
        void set_y(float y);
        /*! \brief Gets the y-coordinate of the point
        */
        float get_y();

        /*! \brief Gets the name of the Landmark object the point was derived from
        */
        Glib::ustring get_landmark_name();

        void set_landmark_name(Glib::ustring);

        void draw(shared_ptr<Cairo::Context> context, bool selected);

        /*! \brief Gets the absolute value (distrance from (0,0)) of the point
        */
        float abs();

        Point operator-(const Point& subtrahend);
        Point operator+(const Point& summand);
        Point operator*(const float&);
        Point operator/(const float&);
    protected:
    private:
        float m_x, m_y;
        Glib::ustring m_landmark_name;
};

#endif // POINT_H
