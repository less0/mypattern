#include "floatpatternparameter.h"

FloatPatternParameter::FloatPatternParameter(Glib::ustring name)
{
    this->set_name(name);
    this->m_rangeType = VALUERANGETYPE_UNKNOWN;
}

FloatPatternParameter::FloatPatternParameter(Glib::ustring  name,
                                             list<float>    valueRange,
                                             ValueRangeType valueRangeType)
{
    this->set_name(name);

    if(valueRangeType == VALUERANGETYPE_UNKNOWN)
    {
        //guess ValueRangeType
        switch(valueRange.size())
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

        m_valueRange = valueRange;
    }
    else
    {
        //! \todo Perform sanity check?
        m_rangeType = valueRangeType;
        m_valueRange = valueRange;
    }
}

FloatPatternParameter::~FloatPatternParameter()
{
    //dtor
}

Glib::ustring FloatPatternParameter::get_xml()
{
    //! \todo Implement XML output
    return "";
}

void FloatPatternParameter::parse_value_range(Glib::ustring valueRange)
{
    size_t spaceIndex = 0;

    Glib::ustring substring = "";
    m_valueRange = list<float>();

    while(spaceIndex >= 0)
    {
        size_t oldIndex = spaceIndex;
        spaceIndex = valueRange.find(" ", oldIndex+1);

        if(spaceIndex >= 0)
        {
            size_t start, n;

            if(oldIndex > 0 || (oldIndex == 0 && valueRange[oldIndex] == ' '))
                start = oldIndex + 1;
            else
                start = oldIndex;

            n = (spaceIndex - 1 - start) + 1;

            substring = valueRange.substr(start, n);
        }
        else
        {
            size_t start, n;

            if(oldIndex > 0 || (oldIndex == 0 && valueRange[oldIndex] == ' '))
                start = oldIndex + 1;
            else
                start = oldIndex;

            n = valueRange.length() - start;

            substring = valueRange.substr(start, n);
        }

        //parse substring
        bool parseError         = false;
        float parsedValue       = 0.0f;
        float decimalDecade     = 1;
        int exponent            = 0;
        bool negative           = false;
        bool comma              = false;
        bool parseExponent      = false;
        bool exponentNegative   = false;

        size_t parseIndex       = 0;

        if(substring[parseIndex] == '-')
        {
            negative = true;
            parseIndex++;
        }

        while(parseIndex < substring.length())
        {
            if(((int)substring[parseIndex] - 48) >= 0 && ((int)substring[parseIndex] - 48) <= 9)
            {
                int digit = (int)substring[parseIndex]-48;

                if(parseExponent)
                    exponent = exponent * 10 + digit;
                else if(comma)
                {
                    parsedValue = parsedValue + ((float)digit)/decimalDecade;
                    decimalDecade++;
                }
                else
                {
                    parsedValue *= 10.0;
                    parsedValue += (float)digit;
                }
            }

            if(substring[parseIndex] == 'E' || substring[parseIndex] == 'e')
            {
                //there's been an 'E' or 'e' already
                if(parseExponent)
                {
                    parseError = true;
                    break;
                }

                if(parseIndex < (substring.length()-1))
                {
                    if(substring[parseIndex+1] == '-')
                    {
                        exponentNegative = true;
                        parseIndex++;
                    }
                    else if(substring[parseIndex + 1] == '+')
                    {
                        exponentNegative = false;
                        parseIndex++;
                    }
                }


                parseExponent = true;
            }

        }

        parsedValue = (negative ? -1.0f : 1.0f) * parsedValue * pow(10.0, (float)exponent * (exponentNegative ? -1.0f : 1.0f));

        //add to list
        if(!parseError)
            m_valueRange.push_back(parsedValue);
    }

    //guess ValueRangeType
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
