#ifndef PAPERSETTINGS_H
#define PAPERSETTINGS_H

#include "units.h"
#include <array>

using namespace std;

namespace MyPattern
{
    namespace Draw
    {
        /*! \brief Stores informations about the paper settings for printing
        */
        struct PaperSettings
        {
            float width;
            float height;
            Units units;
            float margins_left;
            float margins_top;
            float margins_right;
            float margins_bottom;
        };
    }
}


#endif // PAPERSETTINGS_H
