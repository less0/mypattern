#ifndef PATTERNOBJECT_H
#define PATTERNOBJECT_H

#include <string>
#include "objecttype.h"

using namespace std;

namespace MyPattern
{
    namespace Base
    {
        class PatternObject
        {
            public:
                PatternObject();
                PatternObject(const PatternObject&);
                virtual ~PatternObject();

                /** \brief Gets the type of the object
                *
                */
                ObjectType get_object_type()
                {
                    return m_type;
                }

                /** \brief Gets the name of the object
                */
                virtual string get_name() = 0;

                static char get_object_prefix(ObjectType);
            protected:
                PatternObject(ObjectType type);
                ObjectType m_type;
            private:

        };
    }
}


#endif // PATTERNOBJECT_H
