#include "glibmm/ustring.h"

#ifndef USER_H
#define USER_H


class User
{
    public:
        User();
        virtual ~User();
        virtual Glib::ustring get_name() = 0;

    protected:
    private:
};

#endif // USER_H
