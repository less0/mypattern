#ifndef MEASURES_H
#define MEASURES_H

#include "measurevalue.h"
#include "mypattern-data.h"

#include <memory>
#include <list>
#include "glibmm/ustring.h"

using namespace std;
using namespace Glib;
using namespace MyPattern::Data;

namespace MyPattern
{
    namespace Base
    {
        class Measures
        {
            public:
                Measures();
                virtual ~Measures();

                shared_ptr<MeasureValue> define(Glib::ustring name, Glib::ustring comment, double default_value);
                bool remove(ustring name);
                bool remove(shared_ptr<MeasureValue>);

                list<shared_ptr<MeasureValue>> get_measure_values();

                static shared_ptr<Measures> deserialize_from_xml(shared_ptr<XmlNode> node);
            protected:
            private:
                list<shared_ptr<MeasureValue>> m_measureValues;
        };
    }
}


#endif // MEASURES_H
