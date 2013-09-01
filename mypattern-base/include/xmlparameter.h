#ifndef XMLPARAMETER_H
#define XMLPARAMETER_H

#include "glibmm/ustring.h"
#include "glibmm/regex.h"
#include <list>

using namespace std;

class XmlParameter
{
    public:
        XmlParameter();
        XmlParameter(Glib::ustring name, Glib::ustring value);
        XmlParameter(const XmlParameter& parameter);
        /** \brief Gets the name of the parameter
        *
        */
        Glib::ustring get_name();
        void set_name(Glib::ustring);
        Glib::ustring get_value();
        void set_value(Glib::ustring);
        /** \brief Parses a list of XmlParameter objects from a valid XML-Tag.
        *
        * This function takes an XML-tag and searches key-value-pairs int the format key="value"
        * in the tag. Please note, that escaped strings are NOT considered at the moment, therefor
        * a key-value-pair like key="value \"stuff\"" will actually find the key 'key' and the
        * value 'value \', the part after the quotation mark will be ignored, because it does not
        * match the expected key-value-pair format
        *
        */
        static list<XmlParameter> parse_from_tag(Glib::ustring tag);
        /** \brief Parses a key-value-pair as given in the XML-tag.
        *
        * This function takes a key-value-pair in the form key="value" and creates a new
        * XmlParameter with the corresponding key and value.
        */
        static XmlParameter parse(Glib::ustring key_value_pair);
    protected:
    private:
        Glib::ustring m_key;
        Glib::ustring m_value;
};

#endif // XMLPARAMETER_H
