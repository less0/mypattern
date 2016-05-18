#include "valuerangetype.h"
#include <string>
#include "valuerangetype.h"
#include <patternparameter.h>
#include <list>

#ifndef FLOATPATTERNPARAMETER_H
#define FLOATPATTERNPARAMETER_H

#include "math.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class FloatPatternParameter : public PatternParameter
        {
            public:
                FloatPatternParameter(string name);
                FloatPatternParameter(string name,
                                      list<float> valueRange,
                                      ValueRangeType type = VALUERANGETYPE_UNKNOWN);
                virtual ~FloatPatternParameter();

                void parse_value_range(string valueRange);

                //! \todo Implement get_default_value (add a set_default_value, too?)
                float get_default_value();
            protected:
            private:
                list<float> m_valueRange;
                ValueRangeType m_rangeType;

                bool try_parse_value(string, float*);
        };
    }
}


#endif // FLOATPATTERNPARAMETER_H
