#ifndef CURVEDEFINITION_H
#define CURVEDEFINITION_H

#include "landmark.h"
#include "beziercomplex.h"

#include "glibmm/ustring.h"
#include <list>

using namespace Glib;
using namespace std;

/** \brief Defines an abstract definition for a curve in a pattern
*
* \todo Define and implement member functions
*/
class CurveDefinition
{
    public:
        //ctors and dtors
        virtual ~CurveDefinition();
        //

        //pure virtual functions
        //these functions are overwritten in the actual implementtations of curves
        virtual int get_min_landmarks() = 0;
        virtual int get_max_landmarks() = 0;
        virtual BezierComplex get_bezier(list<Point>) = 0;
        virtual ustring get_xml() = 0;


        ustring get_name();
        /*! \brief Sets the name of the CurveDefinition
        *
        * This function sets the name of a CurveDefinition object. CurveDefinition must have unique*
        * names within the PatternDefinition
        */
        bool set_name(ustring);

        /*! \brief Adds a Landmark to the end of the list of landmarks in the CurveDefinition
        *
        * This function adds a Landmark too the list of Landmark objects in the CurveDefinifion. The
        * Landmark is added after the last landmark
        * \todo This way recreating the landmarks from XML is quite hard, maybe the curves should
        * only reference the names of the landmarks
        * \todo Implement add_landmark
        */
        bool add_landmark(shared_ptr<Landmark>);
        /*! \brief Adds a Landmark to list of landmarks in the CurveDefinition
        *
        * This function adds a Landmark too the list of Landmark objects in the CurveDeinifion. The
        * Landmark is added after a Landmark with a given name.
        * \param landmark Pointer to a Landmark object to add.
        * \param after Name of the landmark to add the new object after
        * \todo Implement add_landmark
        * \todo This way recreating the landmarks from XML is quite hard, maybe the curves should
        * only reference the names of the landmarks
        */
        bool add_landmark(shared_ptr<Landmark> landmark, ustring after);
        /*! \brief Gets the names of Landmarks in the current CurveDefinition
        *
        * \return A list with all Landmark names in the CurveDefinition in the correct order
        */
        list<ustring> get_landmark_names();
        /*! \brief Removes a landmark from the list of Landmark objects
        *
        * \param name Name of the Landmark to remove, please note
        */
        bool remove_landmark(ustring name);
        /** \brief Gets a signal to add a function to to request a name change
        */
        sigc::signal2<bool,Glib::ustring,ObjectType> signal_name_change_request();

        /** \brief Creates an CurveDefinition object from XML data
        *
        *
        */
        static shared_ptr<CurveDefinition> get_from_xml(ustring);

    protected:
    private:
        ustring m_name;
        sigc::signal2<bool, Glib::ustring, ObjectType> request_name_change;
        list<shared_ptr<Landmark>> m_landmarks;
};

#endif // CURVEDEFINITION_H
