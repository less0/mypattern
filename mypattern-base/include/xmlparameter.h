#ifndef XMLPARAMETER_H
#define XMLPARAMETER_H

#include "glibmm/ustring.h"

class XmlParameter
{
    public:
        XmlParameter();
        XmlParameter(const XmlParameter& parameter);
        Glib::ustring get_name();
        void set_name(Glib::ustring);
        Glib::ustring get_value();
        void set_value(Glib::ustring);
    protected:
    private:
};

#endif // XMLPARAMETER_H
