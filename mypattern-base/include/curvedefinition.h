#ifndef CURVEDEFINITION_H
#define CURVEDEFINITION_H

#include "landmark.h"
#include "beziercomplex.h"

#include "glibmm/ustring.h"
#include <list>

using namespace Glib;
using namespace std;

namespace MyPattern
{
    namespace Base
    {
        /** \brief Defines an abstract definition for a curve in a pattern
        *
        * \todo Define and implement member functions
        */
        class CurveDefinition : public PatternObject
        {
            public:
                //ctors and dtors
                virtual ~CurveDefinition()
                {}

                //pure virtual functions
                //these functions are overwritten in the actual implementations of curves
                /*!\brief Gets the minimum number of Landmarks that are required for the curve */
                virtual int get_min_landmarks() = 0;
                /*!\brief Gets the maximum number of Landmarks that are required for the curve */
                virtual int get_max_landmarks() = 0;
                /*!\brief Calculates the curve and returns a BezierComplex, which is a complex curve
                    assembled from single Bézier curves
                */
                virtual BezierComplex get_bezier(list<Point>) = 0;

                ustring get_name();
                /*! \brief Sets the name of the CurveDefinition
                *
                * This function sets the name of a CurveDefinition object.
                * CurveDefinition must have unique names within the
                * PatternDefinition, thus the curve definition holds a reference
                * to a function to call on the PatternDefinition and request a
                * name change. If the new name has not been taken yet, the name
                * change is granted and the name of the CurveDefinition is
                * changed
                * \param  New name of the CurveDefinition
                * \return true if the new name was granted by the
                * PatternDefinition the CurveDefinition belongs to, false
                * otherwise
                */
                bool set_name(ustring);

                /*! \brief Sets the names of the Landmarks of the current CurveDefinition
                 */
                void set_landmarks(list<ustring>);

                /*! \brief Gets the names of Landmarks in the current CurveDefinition
                *
                * \return A list with all Landmark names in the CurveDefinition
                * in the correct order
                */
                list<ustring> get_landmarks();

                /** \brief Gets a signal to add a function to to request a name change
                */
                sigc::signal1<bool, Glib::ustring> signal_name_change_request;
                sigc::signal0<void> signal_name_changed;

                sigc::signal1<bool, list<ustring>> signal_request_change;
                sigc::signal0<void> signal_changed;
            protected:
            private:
                ustring m_name;
                list<Glib::ustring> m_landmarks;
                sigc::signal2<bool, Glib::ustring, ObjectType> request_name_change;

        };
    }
}


#endif // CURVEDEFINITION_H
