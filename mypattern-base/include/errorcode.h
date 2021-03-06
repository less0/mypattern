#ifndef ERRORCODE_H_INCLUDED
#define ERRORCODE_H_INCLUDED

namespace MyPattern
{
    namespace Base
    {
        enum ErrorCode {
            ERR_OK,
            ERR_GENERAL,
            ERR_CIRCULAR_DEPENDENCY,
            ERR_CURVE_NOT_FOUND,
            ERR_POINT_NOT_FOUND,
            ERR_MEASURE_NOT_DEFINED,
        };
    }
}



#endif // ERRORCODE_H_INCLUDED
