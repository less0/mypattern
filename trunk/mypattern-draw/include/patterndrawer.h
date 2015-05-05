#ifndef PATTERNDRAWER_H
#define PATTERNDRAWER_H

#include <pattern.h>
#include <papersettings.h>
#include "size.h"
#include <memory>

using namespace std;

namespace MyPattern
{
    namespace Draw
    {
        class PatternDrawer
        {
            public:
                /*! \brief Draws the whole pattern to the current context
                */
                virtual void draw(MyPattern::Base::Part) = 0;
                /*! \brief Draws a single page of the pattern to the current context
                */
                virtual void draw_page(MyPattern::Base::Part, int, int) = 0;
                /*! \brief Gets the size of a part in the current context
                */
                virtual MyPattern::Draw::Size get_size(MyPattern::Base::Part) = 0;


                void set_paper_settings(const PaperSettings&);
            protected:
                PaperSettings m_paperSettings;
            private:
        };
    }
}


#endif // PATTERNDRAWER_H
