#ifndef CAIROPATTERNDRAWER_H
#define CAIROPATTERNDRAWER_H

#include <patterndrawer.h>
#include <coordinatetransformation.h>
#include <list>
#include <glibmm/ustring.h>

namespace MyPattern
{
    namespace Draw
    {
        class CairoPatternDrawer : public PatternDrawer
        {
            public:
                CairoPatternDrawer(Cairo::RefPtr<Cairo::Context> context, shared_ptr<CoordinateTransformation> coordinateTransformation);
                ~CairoPatternDrawer();

                void draw(MyPattern::Base::Part);
                void draw_page(MyPattern::Base::Part, int, int);
				void set_selected_landmarks(list<Glib::ustring> selectedLandmarks);
				void set_selected_curves(list<Glib::ustring>);
                MyPattern::Draw::Size get_size(MyPattern::Base::Part);
            protected:
            private:
                Cairo::RefPtr<Cairo::Context> m_cairoContext;
				shared_ptr<CoordinateTransformation> m_coordinateTransformation;
				list<Glib::ustring> m_selectedLandmarks;
				list<Glib::ustring> m_selectedCurves;
        };
    }
}


#endif // CAIROPATTERNDRAWER_H
