#ifndef BEZIER_H
#define BEZIER_H

#include "point.h"
#include <limits>
#include <cmath>
#include <array>
#include <memory>
#include "cairomm/cairomm.h"

using namespace std;

/*! \brief Defines a single cubic bezier curve
*
* Patterns are - at the lowest level - assembled from bezier curves. This class defines a single
* bezier curve with some helper functions, like drawing with Cairomm and distance calculations.
*/
class Bezier
{
    public:
        Bezier(array<Point,4> points);
        /*! \brief Copy constructor that creates a new Bezier curve based on an existing
        * one.
        */
        Bezier(const Bezier& bezier);
        Bezier();

        /*! \brief Draws the bezier curve to a cairo context
        */
        void draw(shared_ptr<Cairo::Context> context);

        /*! \brief Approximates the length of the Bezier
        */
        float get_length();
        /*! \brief This function approximates the distance of a point to the Bezier
        *
        * This gives an approximation of the distance of a point to the Bezier. The point is
        * approximated by measuring the euclidean distance to a number of points on the Bezier.
        * \todo Implement solution based on analytical considerations, e.g.
        * http://jazzros.blogspot.de/2011/03/projecting-point-on-bezier-curve.html
        */
        float get_distance(Point click);
        /** \brief Gets a coordinate on the Bezier curve given a fraction of the curve
        *
        */
        Point get_coordinate(float);
    protected:
    private:
        array<Point,4> m_points;

        /*! Brief gets the value of the Bernstein-Polynomial B_{i,n}(t)
        */
        float bernstein(float t, int i, int n);
        /*! \brief Gets the binomial coefficient (n over k)
        *
        */
        float binom(int n,int k);
};

#endif // BEZIER_H
