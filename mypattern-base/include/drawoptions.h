#ifndef DRAWOPTIONS_H
#define DRAWOPTIONS_H

#include "papersettings.h"
#include "patternobject.h"
#include <memory>

namespace MyPattern
{
    namespace Base
    {
        class DrawOptions
        {
            public:
                DrawOptions();

                PaperSettings get_paper_settings();
                void set_paper_settings(const PaperSettings&);
            protected:
            private:
        };
    }
}


#endif // DRAWOPTIONS_H
