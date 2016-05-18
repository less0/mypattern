#ifndef PATTERNPARAMETERVALUE_H
#define PATTERNPARAMETERVALUE_H

#include <string>

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class PatternParameterValue
        {
            public:
                PatternParameterValue();
                virtual ~PatternParameterValue();

                void set_parameterName(string name);
                string get_paramterName();

            protected:
            private:
        };
    }
}



#endif // PATTERNPARAMETERVALUE_H
