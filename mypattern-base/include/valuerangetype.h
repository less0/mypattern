#ifndef VALUERANGETYPE_H_INCLUDED
#define VALUERANGETYPE_H_INCLUDED

namespace MyPattern
{
    namespace Base
    {
        enum ValueRangeType
        {
            VALUERANGETYPE_UNKNOWN,
            VALUERANGETYPE_FREE,
            VALUERANGETYPE_DISCRETE,
            VALUERANGETYPE_INTERVAL,
            VALUERANGETYPE_UPPERLIMIT,
            VALUERANGETYPE_LOWERLIMIT
        };
    }
}

#endif // VALUERANGETYPE_H_INCLUDED
