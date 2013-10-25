#ifndef PATTERNDRAWER_H
#define PATTERNDRAWER_H

#include <pattern.h>
#include <papersettings.h>

namespace MyPattern
{
    namespace Draw
    {
        class PatternDrawer
        {
            public:
                PatternDrawer();
                virtual ~PatternDrawer();

                virtual void draw(MyPattern::Base::Pattern) = 0;

                void set_paper_settings(PaperSettings);
            protected:
            private:
        };
    }
}


#endif // PATTERNDRAWER_H
