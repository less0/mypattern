#include <string>
#include <list>

#ifndef INTPATTERNPARAMETER_H
#define INTPATTERNPARAMETER_H

#include <patternparameter.h>
#include <valuerangetype.h>

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class IntPatternParameter : public PatternParameter
        {
            public:
                IntPatternParameter(string name);
                IntPatternParameter(string name, list<int> valueRange, ValueRangeType valueRangeType = VALUERANGETYPE_UNKNOWN);
                virtual ~IntPatternParameter();


                void parse_value_range(string valueRange);

                //! \todo Implement get_default_value (add a set_default_value, too?)
                int get_default_value();
            protected:
            private:
                list<int> m_valueRange;
                ValueRangeType m_rangeType;
        };
    }
}


#endif // INTPATTERNPARAMETER_H
