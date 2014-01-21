#include "intpatternparameter.h"

using namespace MyPattern::Base;

//! \todo Implement the functions of IntPatternParameter

IntPatternParameter::IntPatternParameter(Glib::ustring name, std::list<int> valueRange, ValueRangeType valueRangeType)
{
    this->set_name(name);

    if(valueRangeType == VALUERANGETYPE_UNKNOWN)
    {
        //guess the valuerange type from number of parameters
        switch(valueRange.size())
        {
        case 0:
            m_rangeType = VALUERANGETYPE_FREE;
            break;
        case 1:
            //! \todo guess UPPER vs. LOWER limit based on the value
            m_rangeType = VALUERANGETYPE_UPPERLIMIT;
            break;
        case 2:
            m_rangeType = VALUERANGETYPE_INTERVAL;
            break;
        default:
            m_rangeType = VALUERANGETYPE_DISCRETE;
        }

        this->m_valueRange = valueRange;
    }
    else
    {
        //! \todo perform sanity check?
        this->m_valueRange = valueRange;
        this->m_rangeType = valueRangeType;
    }
}

IntPatternParameter::IntPatternParameter(Glib::ustring name)
{
    this->set_name(name);
    this->m_rangeType = VALUERANGETYPE_UNKNOWN;
}

IntPatternParameter::~IntPatternParameter()
{
    //dtor
}

void IntPatternParameter::parse_value_range(Glib::ustring valueRange)
{
    size_t spaceIndex = 0;
    Glib::ustring substring = "";

    m_valueRange = std::list<int>();

    while(spaceIndex >= 0)
    {
        //get the substring between two spaces
        size_t oldIndex = spaceIndex;
        spaceIndex = valueRange.find(" ", oldIndex+1);

        if(spaceIndex >= 0)
        {
            size_t start, n;

            if(oldIndex > 0 || (oldIndex == 0 && valueRange[oldIndex]==' '))
                start = oldIndex + 1;
            else
                start = oldIndex;

            n = (spaceIndex - 1 - start) + 1;

            substring = valueRange.substr(start, n);
        }
        else
        {
            size_t start, n;

            if(oldIndex > 0 || (oldIndex==0 && valueRange[oldIndex]==' '))
                start = oldIndex + 1;
            else
                start = oldIndex;

            n = valueRange.length() - start;

            substring = valueRange.substr(start, n);
        }

        //now parse the substring
        bool negative       = false;
        int parsedValue     = 0;
        size_t parseIndex   = 0;
        bool parseError    = false;

        if(substring[0] == '-')
        {
            negative    = true;
            parseIndex  = 1;
        }

        while(parseIndex < substring.length())
        {
            //! \todo Check values in ASCII-Table
            if(((int)substring[parseIndex] - 48) >= 0 && ((int)substring[parseIndex] - 48) <= 9)
            {
                parsedValue *= 10;
                parsedValue += ((int)substring[parseIndex]-48);
            }
            else
            {
                parseError = true;
                break;
            }

            parseIndex++;
        }

        if(negative)
            parsedValue *= -1;

        //add to the list
        if(!parseError)
            m_valueRange.push_back(parsedValue);
    }

    //estimate valueRangeType
    switch(m_valueRange.size())
    {
    case 0:
        m_rangeType = VALUERANGETYPE_FREE;
        break;
    case 1:
        m_rangeType = VALUERANGETYPE_UPPERLIMIT;
        break;
    case 2:
        m_rangeType = VALUERANGETYPE_INTERVAL;
        break;
    default:
        m_rangeType = VALUERANGETYPE_DISCRETE;
    }
}
