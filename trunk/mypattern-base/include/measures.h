#ifndef MEASURES_H
#define MEASURES_H

#include "measurevalue.h"

#include <memory>
#include <list>
#include "glibmm/ustring.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class Measures
        {
            public:
                Measures();
                virtual ~Measures();

                shared_ptr<MeasureValue> define(Glib::ustring name, Glib::ustring comment);
                list<shared_ptr<MeasureValue>> get_measure_values();

            protected:
            private:
                list<shared_ptr<MeasureValue>> m_measureValues;
        };
    }
}


#endif // MEASURES_H
