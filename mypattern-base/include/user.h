#include "glibmm/ustring.h"

#ifndef USER_H
#define USER_H

namespace MyPattern
{
    namespace Base
    {
        ///\todo User class may be misplaced in this module
        class User
        {
            public:
                User();
                virtual ~User();
                virtual Glib::ustring get_name() = 0;

            protected:
            private:
        };
    }
}

#endif // USER_H
