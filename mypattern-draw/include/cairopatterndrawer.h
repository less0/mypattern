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
            protected:
            private:
                Cairo::RefPtr<Cairo::Context> m_cairoContext;
        };
    }
}


#endif // CAIROPATTERNDRAWER_H
