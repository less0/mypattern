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
#include "evaluation/formula/term.h"
#include "patternobject.h"
#include "evaluation/evaluationtreeobserver.h"

using namespace std;
using namespace MyPattern::Base::Evaluation::Formula;
using namespace MyPattern::Base::Evaluation;

namespace MyPattern
{
    namespace Base
    {
        /*! \brief Abstract pparametrizable representation of points in the pattern.
        *
        *
        */
        class Landmark : public PatternObject
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
		* \param strip_params If true (default), the parameters of symbolic terms are 
		* removed, e.g. to resolve the dependencies in the evaluation tree. If false
		* the parameters are maintained, e.g. for actual evaluation. 
                */
                list<Glib::ustring> depends_on(bool strip_params = true);

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

		/*! \brief Gets the name of the Landmark 
		 */
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

//                void add_observer(shared_ptr<EvaluationTreeObserver>);
//                void remove_observer(shared_ptr<EvaluationTreeObserver>);

                /*! \brief Gets a signal that's emitted to request a name change
                *
                * \see set_name
                */
                sigc::signal1<bool,ustring> signal_name_change_request;

                /*! \brief Gets the signal that is emitted when the Landmark has changed
                */
                sigc::signal0<void> signal_changed;

                /*! \brief Gets the signal that is emitted when the Landmarks name has changed
                *
                */
                sigc::signal2<void, shared_ptr<Landmark>, Glib::ustring> signal_name_changed;

                /*! \brief Signal that is emitted when the landmarks definition is to be changed
                 *
                 * Changes in a Landmark's definition are only permitted if the changes are valid,
                 * i.e. when the formulae can be parsed, all dependencies can be resolved and there
                 * are no cyclic dependencies in the evaluation tree. If a landmarks is tried to be
                 * changed, it requests the change from the associated LandmarkTreeNode, which
                 * itself passes the request to EvaluationRoot.
		 * \see set_definition_x set_definition_y
                 */
                sigc::signal1<bool, list<ustring>> signal_change_request;
            private:
                //data
                Glib::ustring m_name; /*!<\brief Name of the Landmark */
                /*! \brief Textual representation of the formula to calculate the x-coordinate of 
		 * the Landmark
		 *
		 */
		Glib::ustring m_x_definition;
		/*! \brief Textual representation of the formula to calculate the y-coordinate of 
		 * the Landmark
		 */
                Glib::ustring m_y_definition;

                shared_ptr<Term> m_x_term;
                shared_ptr<Term> m_y_term;

		/*! \brief Concatenates two lists of dependency symbols and strips the argumenta if
		 * desired
		 * \see depends_on
		 */
                list<ustring> depends_on(list<ustring>, list<ustring>, bool strip_argument);
        };
    }
}


#endif // LANDMARK_H
