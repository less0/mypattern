#ifndef PART_H
#define PART_H

#include <list>
#include <memory>


#include "glibmm/ustring.h"
#include "cairomm/context.h"

#include "point.h"
#include "beziercomplex.h"
#include "patternobject.h"
//#include "size.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class Part
        {
            public:
                Part(Glib::ustring,
                     list<Point> points,
                     list<BezierComplex> curves);
                //copy ctor
                Part(const Part&);
                virtual ~Part();

//                /*! \brief Draws the part in the canvas
//                */
//                void draw(shared_ptr<Cairo::Context>);
//                /*! \brief Draws a single page with respect to the PaperSize in the DrawOption object
//                *
//                * \param context Cairo::Context object
//                * \param options
//                */
//                void draw(shared_ptr<Cairo::Context> context,
//                          shared_ptr<DrawOptions> options,
//                          array<int,2> page);

//                /*! \brief Gets the number of pages with repsect to a DrawOption object
//                */
//                array<int,2> get_pages(shared_ptr<Cairo::Context> context,
//                                       shared_ptr<DrawOptions> options);


//                Size get_size();
                Glib::ustring get_name();

                void set_name(Glib::ustring);

                void click(Point click /* add parameter for modifiers*/);


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
                Glib::ustring m_name;
                list<BezierComplex> m_curves;
                list<Point> m_points;
//                bool is_selected(Glib::ustring object_name, ObjectType object_type);
        };

    }
}

#endif // PART_H
