#ifndef PART_H
#define PART_H

#include <list>
#include <memory>


#include <string>

#include "point.h"
#include "beziercomplex.h"
#include "patternobject.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class Part
        {
            public:
                Part(string,
                     list<Point> points,
                     list<BezierComplex> curves);
                //copy ctor
                Part(const Part&);
                virtual ~Part();


                string get_name();

                void set_name(string);

                /*! \brief Is called when a user makes a click, to select objects
                 * \note This should be moved to some other place - maybe selected objects
                * by name.
                 */
                void click(Point click /* add parameter for modifiers*/);

                /*! \brief Gets a list of all the points in the pattern
                 */
                list<Point> get_points()
                {
                    return m_points;
                }

                list<BezierComplex> get_curves()
                {
                    return m_curves;
                }

                /*! \brief Gets a list of all selected pattern objects
                *
                * Users can select pattern objects (i.e. points, curves) in te edit view. This function
                * returns all selected pattern objects in the order the user selected this objects.
                */
                shared_ptr<PatternObject> get_selected_objects();

                /*! \brief Clears the list of selected objects in the pattern
                */
                void clear_selected_objects();
            protected:
            private:
                string m_name;
                list<BezierComplex> m_curves;
                list<Point> m_points;
//                bool is_selected(string object_name, ObjectType object_type);
        };

    }
}

#endif // PART_H
