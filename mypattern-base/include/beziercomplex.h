#ifndef BEZIERCOMPLEX_H
#define BEZIERCOMPLEX_H

#include "point.h"
#include "bezier.h"

#include <string>

#include <list>
#include <memory>
#include <limits>

using namespace std;

namespace MyPattern
{
    namespace Base
	{
        /** \brief A class to define a complex curve consisting of multiple
        * B�zier curves.
        *
        * Sewing patterns demand curves which are not always mappable to a
        * single B�zier curve. This class defines complex curves which suit the
        * demands of creating sewing ppatterns better.
        */
        class BezierComplex
        {
            public:
                BezierComplex(list<Bezier>);
                BezierComplex(list<Bezier>, string name);
		BezierComplex();
                BezierComplex(const BezierComplex& instance_to_copy);

                /** \brief Approximates the length of a complex B�zier
                *
                *
                */
                double get_length();
                /** \brief Gets a point on the curve given a fraction of the
                * curve
                *
                *  The function gets a point that lies on the curve, that is
                * defined by a fraction of the
                * curve.
                *
                * \param rel_length This is a fraction of the curve (in
                * [.0 1.0]) and equals the t parameter for a single B�zier
                * \return The coordinate on the curve
                */
                Point get_coordinate(double rel_length);

                /** \brief Gets the name of the BezierComplex object
                *
                * Gets the name of the BezierComplex object. This genrally
                * should match the CurveDefinition the BezierComplex has been
                * created from.
                * /return Name of the BezierComplex object
                */
                string get_name();
                /** \brief Sets the name of a BezierComplex object
                *
                * This function sets the name of a BezierComplex object,
                * generally this has to match the name of the CurveDefinition
                * the BezierComplex has been generated from
                */
                void set_name(string name);

                /** \brief Adds a Bezier to the BezierComplex
                */
                void add_bezier(Bezier);
				
				list<Bezier> get_beziers();
                /** \brief Gets the shortest distance of a Point to the
                * BezierComplex
                */
                double get_distance(Point);
            protected:
            private:
                list<Bezier> m_bezier_curves;
                string m_curve_name;
        };
    }
}


#endif // BEZIERCOMPLEX_H
