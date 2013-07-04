#include "glibmm/ustring.h"

#ifndef USER_H
#define USER_H


class User
{
    public:
        User();
        virtual ~User();

        virtual Glib::ustring get_xml() = 0;
        virtual Glib::ustring get_name() = 0;

        static User* get_from_xml(Glib::ustring xml);
    protected:
    private:
};

#endif // USER_H
