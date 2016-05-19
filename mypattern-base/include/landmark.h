#ifndef LANDMARK_H
#define LANDMARK_H

#include "point.h"
#include "measures.h"
#include "beziercomplex.h"
#include "patternparametervalue.h"
#include <list>
#include <map>
#include <string>
#include "objecttype.h"
#include "sigc++/sigc++.h"
#include "sigc++/signal.h"
#include "evaluation/formula/term.h"
#include "patternobject.h"
#include "evaluation/evaluationtreeobserver.h"
#include "mypattern-data.h"

using namespace std;
using namespace MyPattern::Base::Evaluation::Formula;
using namespace MyPattern::Base::Evaluation;
using namespace MyPattern::Data;

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
                string get_definition_x();

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
                bool set_definition_x(string);

                string get_definition_y();
                bool set_definition_y(string);

                /*! \brief Gets a list of objects (Landmarks, Curves), Measures, and
                * PatternParameters the Landmark depends on
                *
                * \param strip_params If true (default), the parameters of symbolic terms are
                * removed, e.g. to resolve the dependencies in the evaluation tree. If false
                * the parameters are maintained, e.g. for actual evaluation.
                */
                list<string> depends_on(bool strip_params = true);

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
                Point get_point(map<string,double> value);

                /*! \brief Gets the name of the Landmark
                 */
                string get_name();
                /*! \brief Sets the name of the Landmark
                *
                * This function sets the name of the Landmark. To check if the name is valid, this
                * function emits the signal returned by signal_name_change_request
                * \param name The new name of the Landmark
                * \return True if the name change was allowed, false if the name change request was
                *         denied.
                * \see signal_name_change_request
                */
                bool set_name(string name);

                /*! \brief Gets a signal that's emitted to request a name change
                *
                * \see set_name
                */
                sigc::signal1<bool,string> signal_name_change_request;

                /*! \brief Gets the signal that is emitted when the Landmarks name has changed
                *
                */
                sigc::signal2<void, shared_ptr<Landmark>, string> signal_name_changed;

                /*! \brief Signal that is emitted when the landmarks definition is to be changed
                 *
                 * Changes in a Landmark's definition are only permitted if the changes are valid,
                 * i.e. when the formulae can be parsed, all dependencies can be resolved and there
                 * are no cyclic dependencies in the evaluation tree. If a landmarks is tried to be
                 * changed, it requests the change from the associated LandmarkTreeNode, which
                 * itself passes the request to EvaluationRoot.
                 * \see set_definition_x set_definition_y
                 */
                sigc::signal1<bool, list<string>> signal_change_request;

                /*! \brief Gets the signal that is emitted when the Landmark has changed
                 *
                 * This will usually cause the associated EvaluationTreeNode  to request an
                 * update of its dependencies and then - if the update was successful - notify
                 * all dependent EvaluationTreeNode objects
                */
                sigc::signal0<void> signal_changed;
				
				static shared_ptr<Landmark> deserialize_from_xml(shared_ptr<XmlNode>);
            private:
                //data
                string m_name; /*!<\brief Name of the Landmark */
                /*! \brief Textual representation of the formula to calculate the x-coordinate of
                 * the Landmark
                 *
                 */
                string m_x_definition;
                /*! \brief Textual representation of the formula to calculate the y-coordinate of
                * the Landmark
                */
                string m_y_definition;

                shared_ptr<Term> m_x_term;
                shared_ptr<Term> m_y_term;

                /*! \brief Concatenates two lists of dependency symbols and strips the argumenta if
                 * desired
                 * \see depends_on
                 */
                list<string> depends_on(list<string>, list<string>, bool strip_argument);
        };
    }
}


#endif // LANDMARK_H
