#ifndef BEZIERDEFINITION_H
#define BEZIERDEFINITION_H

#include <curvedefinition.h>
#include <beziercomplex.h>
#include <bezier.h>
#include <list>
#include <array>
#include "glibmm/ustring.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        /*! \brief CurveDefinition for a single Bezier curve
        */
        class BezierDefinition : public CurveDefinition
        {
            public:
                /** \brief Gets the minimum number of Landmarks
                */
                int get_min_landmarks();
                /*! \brief Gets the maximum number of landmarks
                */
                int get_max_landmarks();
                /*! \brief Gets the actual Bezier object given a list of points defining the curve
                */
                BezierComplex get_bezier(list<Point>);

                shared_ptr<CurveDefinition> deserialize_from_xml(XmlNode);
                XmlNode serialize_to_xml();

                Glib::ustring get_class_name();

                BezierDefinition();
                virtual ~BezierDefinition();
            protected:
            private:
        };
    }
}


#endif // BEZIERDEFINITION_H
