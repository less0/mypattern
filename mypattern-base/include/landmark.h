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

/*! \brief Abstract pparametrizable representation of points in the pattern.
*
*
*/
class Landmark
{
    public:
        Landmark();
        virtual ~Landmark();

        /*! \brief Gets the definition for the X-coordinate of the landmark, i.e. the dependency of
         *the X-coordinate on other pattern objects and parameters
        *
        * Landmarks in patterns usually depend on other Landmarks, on Curves or on Parameters of the
        * pattern. The dependency on other pattern objects is defined in a string and passed to this
        * method. When a Pattern is created from a PatternDefinition, these definitions are
        */
        Glib::ustring get_definition_x();
        /*! \brief Sets the definition for the X-coordinate of the landmark, i.e. the dependency of
        * the X-coordinate on other pattern objects and parameters
        *
        * Landmarks in patterns usually depend on other Landmarks, on Curves or on Parameters of the
        * pattern. The dependency on other pattern objects is defined in a string and passed to this
        * method. When a Pattern is created from a PatternDefinition, these definitions are used to
        * evaluate the conditional positions of the landmarks.
        */
        bool set_definition_x(Glib::ustring);

        Glib::ustring get_definition_y();
        bool set_definition_y(Glib::ustring);

        /*! \brief Gets a list of objects (Landmarks, Curves), Measures, and
        * PatternParameters the Landmark depends on
        */
        list<Glib::ustring> depends_on();
        /*! \brief
        *
        * \param measures Object containing body measures
        * \param points List of points created from the landmarks the current landmark depends on
        * \param curves List of curves created from curve definitions the current landmark depends
        * on
        * \param parameterValues List of parameter values the current landmark
        * depends on
        */
        Point get_point(Measures measures,
                        list<Point> points,
                        list<BezierComplex> curves,
                        list<PatternParameterValue> parameterValues);


        Glib::ustring get_name();
        /*! \brief Sets the name of the Landmark
        *
        * This function sets the name of the Landmark. To check if the name is valid, this function
        * calls ths function that's been passed in the add_request_fct function.
        * \param name The new name of the Landmark
        * \return True if the name change was allowed, false if the name change request was denied.
        */
        bool set_name(Glib::ustring name);

        /*! \brief Gets the XML definition for the landmark.
        *
        */
        Glib::ustring get_xml();

        /*! \brief Restores a landmark from XML
        */
        static shared_ptr<Landmark> get_from_xml(Glib::ustring xml);

        /*! \brief Adds a function to request a name change
        *
        * This function takes a function pointer to add to the current Landmark object to request if
        * a name change is valid. Validity of a name change includes the validity of the form of the
        * name as well as the uniqueness of the name.
        * \param request_fct_ptr function pointer to the function to request the name change
        */
        sigc::signal2<bool,Glib::ustring,ObjectType> signal_name_change_request();
    protected:
    private:
        //data
        Glib::ustring m_name;
        Glib::ustring m_x_definition;
        Glib::ustring m_y_definition;

        sigc::signal2<bool,Glib::ustring,ObjectType> m_signal_name_change_request;

        //methods
        bool validate_definition(Glib::ustring definition);


};

#endif // LANDMARK_H
