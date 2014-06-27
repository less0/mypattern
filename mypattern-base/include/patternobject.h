#ifndef PATTERNOBJECT_H
#define PATTERNOBJECT_H

#include "glibmm/ustring.h"
#include "objecttype.h"

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
                virtual Glib::ustring get_name() = 0;

                static char get_object_prefix(ObjectType);
            protected:
                PatternObject(ObjectType type);
                ObjectType m_type;
            private:

        };
    }
}


#endif // PATTERNOBJECT_H
