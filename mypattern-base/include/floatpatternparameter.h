#include "valuerangetype.h"
#include "glibmm/ustring.h"
#include "valuerangetype.h"
#include <patternparameter.h>
#include <list>

#ifndef FLOATPATTERNPARAMETER_H
#define FLOATPATTERNPARAMETER_H

#include "math.h"

using namespace std;

class FloatPatternParameter : public PatternParameter
{
    public:
        FloatPatternParameter(Glib::ustring name);
        FloatPatternParameter(Glib::ustring name, list<float> valueRange, ValueRangeType type = VALUERANGETYPE_UNKNOWN);
        virtual ~FloatPatternParameter();

        //! \todo refactor XML input and output for use with TinyXML
        Glib::ustring get_xml();
        void parse_value_range(Glib::ustring valueRange);

        //! \todo Implement get_default_value (add a set_default_value, too?)
        float get_default_value();
    protected:
    private:
        list<float> m_valueRange;
        ValueRangeType m_rangeType;
};

#endif // FLOATPATTERNPARAMETER_H
