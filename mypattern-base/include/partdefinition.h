#include "measures.h"
#include "patternparametervalue.h"
#include "patternerror.h"
#include "landmark.h"
#include "curvedefinition.h"
#include "part.h"
#include "evaluation/evaluationroot.h"
#include "glibmm/ustring.h"
#include <memory>

#ifndef PARTDEFINITION_H
#define PARTDEFINITION_H

using namespace Glib;
using namespace MyPattern::Data;

namespace MyPattern
{
    namespace Base
    {
        class PartDefinition
        {
            public:
                PartDefinition();
                virtual ~PartDefinition();

                /*! \brief Gets a Part given the Measures and PatternParameterValues
                *
                *
                */
                Part get_part();

                /*! \brief Gets a single landmark
                *
                * \param name Name of the landmark
                */
                shared_ptr<Landmark> get_landmark(Glib::ustring name);

                /*! \brief Gets a list of pointers to all landmarks in the part
                */
                list<shared_ptr<Landmark>> get_landmarks();

                /*! \brief Gets a list of landmark names in the current part
                */
                list<Glib::ustring> get_landmark_names();

                /*! \brief Adds a landmark to the part
                *
                * \param landmark The landmark to add
                */
                bool add_landmark(shared_ptr<Landmark> landmark);

                /*! \brief Gets a curve definition from the current part
                *
                * \param name Name of the curve definition
                */
                shared_ptr<CurveDefinition> get_curve_definition(Glib::ustring name);

                /*! Adds a curve definition to the current part
                *
                * \param definition A curve definition to add
                */

                /*! \brief Gets a list of pointers to all curve definitions
                 * in the part
                 */
                list<shared_ptr<CurveDefinition>> get_curve_definitions();

                /*! \brief Adds a curve definition to the list of curve
                 * definitions in the part
                 */
                bool add_curve_definition(shared_ptr<CurveDefinition> definition);

                /*! \brief Sets the currently available measures
                 *
                 * This method sets the measures used for the calculation of
                 * Landmark objects, etc. If there already is a measureobject
                 * in the part the object is tried to be replaced with
                 * respect to objects depending on MeasureValue object the
                 * Measures object contains, i.e. if some part of the pattern
                 * depends on a MeasureValue that would be removed when replacing
                 * Measures the operation will fail
                 *
                 * \throw UnmetDependenciesException
                 * \todo Maybe introduce a new Exception class for thiscase
                 */
                bool set_measures(shared_ptr<Measures>);

                /*! \brief Gets the currently available measures
                 */
                shared_ptr<Measures> get_measures();

                /*! \brief Gets the name of the part.
                 *
                 */
                Glib::ustring get_name();

                /*! \brief Sets the name of the part
                *
                * This function requests a name change of the part. Since the
                * parts have to have unique names, the request of the name
                * change will be transmitted to the parent pattern, which
                * itself then checks the names of all parts and either allows
                * the name change or not. If and only if the parent pattern
                * allowed the name change, the part internally changes its
                * name. For the parent pattern does not have any information
                * about which part requested the name change, calling this
                * function with the current name of the part will cause an
                * error.
                *
                * \param name Name of the part
                * \return true if the parent pattern allowed the name change,
                * false otherwise
                */
                bool set_name(Glib::ustring name);

                /*! \brief Gets the signal for requesting a name change
                *
                * To maintain the unambiquity of part definitions, each part
                * must request a name change before the name is actually
                * changes. This is accomplished making use of the observer
                * pattern in which the PatternDefinition is the observer and
                * the PartDefinition is the observee. If set_name is called the
                * PartDefinition object emits the signal returned by this
                * function.
                */
                sigc::signal1<bool,Glib::ustring> signal_name_change_request();

                /*! \brief Deserializes a PartDefinition from an XmlNode
                 *
                 * \param node part node to parse
                 * \param measures Measures parsed in PatternDefinition level
                 */
                static shared_ptr<PartDefinition> deserialize_from_xml(
                    shared_ptr<XmlNode> node,
                    shared_ptr<Measures> measures);
            protected:
            private:
                sigc::signal1<bool,Glib::ustring> m_signal_name_change_request;

                list<shared_ptr<CurveDefinition>> m_curve_definitions;
                list<shared_ptr<Landmark>> m_landmarks;
                shared_ptr<Measures> m_measures;

                Glib::ustring m_name;
                MyPattern::Base::Evaluation::EvaluationRoot m_evaluationRoot;
        };

    }
}

#endif // PARTDEFINITION_H
