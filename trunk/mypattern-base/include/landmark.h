#ifndef LANDMARK_H
#define LANDMARK_H

#include "point.h"
#include "measures.h"
#include "beziercomplex.h"
#include "patternparametervalue.h"
#include <list>
#include "glibmm/ustring.h"
#include "objecttype.h"
#include "sigc++/sigc++.h"
#include "sigc++/signal.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        /*! \brief Abstract pparametrizable representation of points in the pattern.
        *
        *
        */
        class Landmark
        {
            public:
                Landmark();
                virtual ~Landmark();

                /*! \brief Gets the definition for the X-coordinate of the landmark,
                * i.e. the dependency of the X-coordinate on other pattern objects
                * and parameters
                *
                * Landmarks in patterns usually depend on other Landmarks, on Curves
                * or on Parameters of the pattern. The dependency on other pattern
                * objects is defined in a string and passed to this method. When a
                * Pattern is created from a PatternDefinition, these definitions are
                */
                Glib::ustring get_definition_x();
                /*! \brief Sets the definition for the X-coordinate of the landmark,
                * i.e. the dependency of the X-coordinate on other pattern objects
                * and parameters
                *
                * Landmarks in patterns usually depend on other Landmarks, on Curves
                * or on Parameters of the pattern. The dependency on other pattern
                * objects is defined in a string and passed to this method. When a
                * Pattern is created from a PatternDefinition, these definitions are
                * used to evaluate the conditional positions of the landmarks.
                */
                bool set_definition_x(Glib::ustring);

                Glib::ustring get_definition_y();
                bool set_definition_y(Glib::ustring);

                /*! \brief Gets a list of objects (Landmarks, Curves), Measures, and
                * PatternParameters the Landmark depends on
                *
                * \todo Change template parameter of return value from Glib::ustring to
                *   PatternObject
                */
                list<Glib::ustring> depends_on();

                /*! \brief Calculates and returns the position of the landmark, given a set of
                *          Measures, Point objects representing the Landmarks this Landmark
                *          depends on, BezierComplex objects representing CurveDefinitions this
                *          Landmark depends on and PatternParameterValues of PatternParameters this
                *          Landmark depends on
                *
                * \param measures Object containing body measures
                * \param points List of points created from the landmarks the current landmark
                *        depends on
                * \param curves List of curves created from curve definitions the current landmark
                *        depends on
                * \param parameterValues List of parameter values the current landmark
                *        depends on
                */
                Point get_point(Measures measures,
                                list<Point> points,
                                list<BezierComplex> curves,
                                list<PatternParameterValue> parameterValues);


                Glib::ustring get_name();
                /*! \brief Sets the name of the Landmark
                *
                * This function sets the name of the Landmark. To check if the name is valid, this
                * function emits the signal returned by signal_name_change_request
                * \param name The new name of the Landmark
                * \return True if the name change was allowed, false if the name change request was
                *         denied.
                * \see signal_name_change_request
                */
                bool set_name(Glib::ustring name);

                /*! \brief Gets a signal that's emitted to request a name change
                *
                * \see set_name
                */
                sigc::signal2<bool,Glib::ustring,ObjectType> signal_name_change_request();

                /*! \brief Gets the signal that is emitted when the Landmark has changed
                */
                sigc::signal1<void, shared_ptr<Landmark>> signal_changed();

                /*! \brief Gets the signal that is emitted when the Landmarks name has changed
                *
                */
                sigc::signal2<void, shared_ptr<Landmark>, Glib::ustring> signal_name_changed();
            private:
                //data
                Glib::ustring m_name;
                Glib::ustring m_x_definition;
                Glib::ustring m_y_definition;

                /*!\brief Requests a name change
                 *
                 * Landmark names are unique, thus the landmark has to request a name change.
                 * Furthermore the pattern has to update all the objects the landmark depends
                 * on.
                 */
                sigc::signal2<bool,Glib::ustring,ObjectType> m_signal_name_change_request;
                /*!\brief Requests a change of the landmark given the new dependencies
                 *
                 * The pattern has to check weather the objects the landmark depends on given
                 * a change of the formula are valid. Thus, Landmark emits a signal with a list
                 * of the new dependencies for the pattern to validate 'em.
                 */
                sigc::signal2<bool,shared_ptr<Landmark>,list<ustring>> m_signal_change_request;
                sigc::signal1<void,shared_ptr<Landmark>> m_signal_changed;
                sigc::signal2<void,shared_ptr<Landmark>, Glib::ustring> m_signal_name_changed;

                //methods
                bool validate_definition(Glib::ustring definition);
        };
    }
}


#endif // LANDMARK_H
