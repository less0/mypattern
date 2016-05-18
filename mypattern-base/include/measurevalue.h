#ifndef MEASUREVALUE_H
#define MEASUREVALUE_H

#include "patternobject.h"
#include <string>
#include "sigc++/sigc++.h"
#include "mypattern-data.h"
#include <memory>

using namespace sigc;
using namespace std;
using namespace MyPattern::Data;

namespace MyPattern
{
    namespace Base
    {
        class MeasureValue : public PatternObject
        {
            public:
                MeasureValue(string name, string description, double default_value);
                MeasureValue(const MeasureValue& valueToCopy);
                virtual ~MeasureValue();

                string get_name();
                string get_description();

                double get_value();
                void set_value(double value);

                signal0<void> signal_changed;
				
				static shared_ptr<MeasureValue> deserialize_from_xml(shared_ptr<XmlNode>);
            protected:
            private:
                string m_name;
                string m_description;
                double m_value;
                double m_default_value;

                bool m_has_value;
        };
    }
}


#endif // MEASUREVALUE_H
