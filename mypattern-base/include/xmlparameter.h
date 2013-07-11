#ifndef XMLPARAMETER_H
#define XMLPARAMETER_H

#include "glibmm/ustring.h"
#include <list>

using namespace std;

class XmlParameter
{
    public:
        XmlParameter();
        XmlParameter(const XmlParameter& parameter);
        Glib::ustring get_name();
        void set_name(Glib::ustring);
        Glib::ustring get_value();
        void set_value(Glib::ustring);
        static list<XmlParameter> parse_from_tag(Glib::ustring tag);
        static XmlParameter parse(Glib::ustring key_value_pair);
    protected:
    private:
        Glib::ustring m_key;
        Glib::ustring m_value;
};

#endif // XMLPARAMETER_H
