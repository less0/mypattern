#include "glibmm/ustring.h"

#ifndef PATTERNPARAMETERVALUE_H
#define PATTERNPARAMETERVALUE_H

namespace MyPattern
{
    namespace Base
    {
        class PatternParameterValue
        {
            public:
                PatternParameterValue();
                virtual ~PatternParameterValue();

                void set_parameterName(Glib::ustring name);
                Glib::ustring get_paramterName();

            protected:
            private:
        };
    }
}



#endif // PATTERNPARAMETERVALUE_H
