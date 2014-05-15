#ifndef MEASUREVALUE_H
#define MEASUREVALUE_H

#include "patternobject.h"
#include "glibmm/ustring.h"
#include "sigc++/sigc++.h"
#include <memory>

using namespace sigc;
using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class MeasureValue : public PatternObject
        {
            public:
                MeasureValue(Glib::ustring name, Glib::ustring description, double default_value);
                MeasureValue(const MeasureValue& valueToCopy);
                virtual ~MeasureValue();

                Glib::ustring get_name();
                Glib::ustring get_description();

                double get_value();
                void set_value(double value);

                signal0<void> signal_changed;
            protected:
            private:
                Glib::ustring m_name;
                Glib::ustring m_description;
                double m_value;
                double m_default_value;

                bool m_has_value;
        };
    }
}


#endif // MEASUREVALUE_H
