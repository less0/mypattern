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
                PatternObject(ObjectType type, Glib::ustring name);
                virtual ~PatternObject();

                /** \brief Sets the type of the object
                *
                * \param objectType Type of the object
                */
                void set_object_type(ObjectType objectType);
                /** \brief Gets the type of the object
                *
                */
                ObjectType get_object_type();

                /** \brief Sets the name of the object
                *
                * Sets the name, to identify the selected object
                */
                void set_object_name(Glib::ustring name);
                /** \brief Gets the name of the object
                */
                Glib::ustring get_object_name();
            protected:
            private:
        };
    }
}


#endif // PATTERNOBJECT_H
