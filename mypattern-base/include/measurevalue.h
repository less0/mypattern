#ifndef MEASUREVALUE_H
#define MEASUREVALUE_H

#include "glibmm/ustring.h"

namespace MyPattern
{
    namespace Base
    {
        class MeasureValue
        {
            public:
                MeasureValue(Glib::ustring name, Glib::ustring description, double value);
                MeasureValue(const MeasureValue& valueToCopy);
                virtual ~MeasureValue();

                Glib::ustring get_name();
                Glib::ustring get_description();

                double get_value();
                void set_value(double value);
            protected:
            private:
                Glib::ustring m_name;
                Glib::ustring m_description;
                double m_value;
        };
    }
}


#endif // MEASUREVALUE_H
