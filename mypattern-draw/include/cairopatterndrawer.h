#ifndef CAIROPATTERNDRAWER_H
#define CAIROPATTERNDRAWER_H

#include <patterndrawer.h>

namespace MyPattern
{
    namespace Draw
    {
        class CairoPatternDrawer : public PatternDrawer
        {
            public:
                CairoPatternDrawer(Cairo::RefPtr<Cairo::Context> context);
                ~CairoPatternDrawer();

                void draw(std::shared_ptr<MyPattern::Base::Part>);
            protected:
            private:
                Cairo::RefPtr<Cairo::Context> m_cairoContext;
        };
    }
}


#endif // CAIROPATTERNDRAWER_H
