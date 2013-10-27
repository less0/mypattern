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
                virtual void draw(MyPattern::Base::Pattern) = 0;
                virtual void draw_page(MyPattern::Base::Pattern, int, int) = 0;
                virtual MyPattern::Draw::Size get_size(MyPattern::Base::Pattern) = 0;

                void set_paper_settings(const PaperSettings&);
            protected:
                PaperSettings m_paperSettings;
            private:
        };
    }
}


#endif // PATTERNDRAWER_H
