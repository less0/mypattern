#include <string>

#ifndef USER_H
#define USER_H

using namespace std;

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
                virtual string get_name() = 0;

            protected:
            private:
        };
    }
}

#endif // USER_H
