#ifndef PATTERNDRAWER_H
#define PATTERNDRAWER_H

#include <pattern.h>
#include <papersettings.h>
#include "size.h"

namespace MyPattern
{
    namespace Draw
    {
        class PatternDrawer
        {
            public:
                virtual void draw(MyPattern::Base::Part) = 0;
                virtual void draw_page(MyPattern::Base::Part, int, int) = 0;
                virtual MyPattern::Draw::Size get_size(MyPattern::Base::Part) = 0;

                void set_paper_settings(const PaperSettings&);
            protected:
                PaperSettings m_paperSettings;
            private:
        };
    }
}


#endif // PATTERNDRAWER_H
