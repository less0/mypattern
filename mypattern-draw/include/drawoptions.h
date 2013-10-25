#ifndef DRAWOPTIONS_H
#define DRAWOPTIONS_H

#include "papersettings.h"
#include "patternobject.h"
#include <memory>

namespace MyPattern
{
    namespace Draw
    {
        class DrawOptions
        {
            public:
                DrawOptions();

                PaperSettings get_paper_settings();
                void set_paper_settings(const PaperSettings&);
            protected:
            private:
                PaperSettings m_paperSettings;
        };
    }
}


#endif // DRAWOPTIONS_H
