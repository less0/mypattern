#include "glibmm/ustring.h"
#include <list>

#ifndef INTPATTERNPARAMETER_H
#define INTPATTERNPARAMETER_H

#include <patternparameter.h>
#include <valuerangetype.h>

using namespace std;

class IntPatternParameter : public PatternParameter
{
    public:
        IntPatternParameter(Glib::ustring name);
        IntPatternParameter(Glib::ustring name, list<int> valueRange, ValueRangeType valueRangeType = VALUERANGETYPE_UNKNOWN);
        virtual ~IntPatternParameter();

        //! \todo Implement XML output
        Glib::ustring get_xml();
        void parse_value_range(Glib::ustring valueRange);

        //! \todo Implement get_default_value (add a set_default_value, too?)
        int get_default_value();
    protected:
    private:
        list<int> m_valueRange;
        ValueRangeType m_rangeType;
};

#endif // INTPATTERNPARAMETER_H
