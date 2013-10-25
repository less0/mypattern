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
        class PaperSettings
        {
            public:
                PaperSettings();
                virtual ~PaperSettings();

                /*! \brief Gets the paper width
                */
                double get_width();
                /*! \brief Sets the paper width
                */
                void set_width(double);
                /*! \brief Gets the paper height
                */
                double get_height();
                void set_height(double);
                /*! \brief Gets the printer margins
                */
                array<double,4> get_margins();

                /*! \brief Sets the printer marginss
                */
                void set_margins(array<double,4>);
                /*! \brief Gets the units of the paper setting values
                */
                Units get_unit();

                void set_unit(Units);

            protected:
            private:
        };
    }
}


#endif // PAPERSETTINGS_H
