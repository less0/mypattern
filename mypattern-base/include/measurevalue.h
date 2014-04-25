#ifndef MEASUREVALUE_H
#define MEASUREVALUE_H

#include "glibmm/ustring.h"
#include "sigc++/sigc++.h"
#include <memory>

using namespace sigc;
using namespace std;

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

                signal1<void, shared_ptr<MeasureValue>> signal_changed()
                {
                    return m_signal_changed;
                }

            protected:
            private:
                Glib::ustring m_name;
                Glib::ustring m_description;
                double m_value;
                signal1<void, shared_ptr<MeasureValue>> m_signal_changed;
        };
    }
}


#endif // MEASUREVALUE_H
