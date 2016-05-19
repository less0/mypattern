#include "floatpatternparameter.h"

using namespace MyPattern::Base;

FloatPatternParameter::FloatPatternParameter(string name)
{
    this->set_name(name);
    this->m_rangeType = VALUERANGETYPE_UNKNOWN;
}

FloatPatternParameter::FloatPatternParameter(string  name,
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

void FloatPatternParameter::parse_value_range(string valueRange)
{
    size_t spaceIndex = 0;

    //prepare REGEX expressions
    string regexFloat = "[\\+\\-]{0,1}[0-9]{1,}(\\.[0-9]{1,}){0,1}([eE][\\+\\-]{0,1}[0-9]{1,}){0,1}";
    string regexUpperLimit = string("^\\<")
        .append(regexFloat)
        .append("$");
    string regexLowerLimit = string("^\\>")
        .append(regexFloat)
        .append("$");
    string regexInterval = string("^")
        .append(regexFloat)
        .append("\\-")
        .append(regexFloat)
        .append("$");
    string regexDiscrete = string("^(")
        .append(regexFloat)
        .append("\\,){0,}(")
        .append(regexFloat)
        .append(")");

    string substring = "";
    m_valueRange = list<float>();

    ///\todo this is not a high performance function, thus the code parsing the
    /// values may be moved to a separate function
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

        float value;

        if(try_parse_value(substring, &value))
        {
            m_valueRange.push_back(value);
        }
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

bool FloatPatternParameter::try_parse_value(string s, float* o)
{
    bool parseError         = false;
    float parsedValue       = 0.0f;
    float decimalDecade     = 1;
    int exponent            = 0;
    bool negative           = false;
    bool comma              = false;
    bool parseExponent      = false;
    bool exponentNegative   = false;

    size_t parseIndex       = 0;

    if(s[parseIndex] == '-')
    {
        negative = true;
        parseIndex++;
    }

    while(parseIndex < s.length())
    {
        if(((int)s[parseIndex] - 48) >= 0 && ((int)s[parseIndex] - 48) <= 9)
        {
            int digit = (int)s[parseIndex]-48;

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

        if(s[parseIndex] == 'E' || s[parseIndex] == 'e')
        {
            //there's been an 'E' or 'e' already
            if(parseExponent)
            {
                parseError = true;
                break;
            }

            if(parseIndex < (s.length()-1))
            {
                if(s[parseIndex+1] == '-')
                {
                    exponentNegative = true;
                    parseIndex++;
                }
                else if(s[parseIndex + 1] == '+')
                {
                    exponentNegative = false;
                    parseIndex++;
                }
            }


            parseExponent = true;
        }
    }

    if(parseError)
    {
        *o = .0;
        return false;
    }

    parsedValue = (negative ? -1.0f : 1.0f) * parsedValue * pow(10.0, (float)exponent * (exponentNegative ? -1.0f : 1.0f));

    *o = parsedValue;
    return true;
}
