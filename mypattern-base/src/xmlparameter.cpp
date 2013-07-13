#include "xmlparameter.h"

XmlParameter::XmlParameter()
{
    //ctor
}

XmlParameter::XmlParameter(const XmlParameter& base)
{
    this->m_key = base.m_key;
    this->m_value = base.m_value;
}

Glib::ustring XmlParameter::get_name()
{
    return Glib::ustring(this->m_key);
}

Glib::ustring XmlParameter::get_value()
{
    return this->m_value;
}

XmlParameter XmlParameter::parse(Glib::ustring key_value_pair)
{
    XmlParameter result;
    int equalSignIndex = key_value_pair.find("=");

    if(equalSignIndex < 0)
    {
        return XmlParameter();
    }

    Glib::ustring key = key_value_pair.substr(0, equalSignIndex);
    Glib::ustring value = key_value_pair.substr(equalSignIndex + 1);

    result.m_key = Glib::ustring(key);
    result.m_value = Glib::ustring(value);

    return XmlParameter(result);
}

list<XmlParameter> XmlParameter::parse_from_tag(Glib::ustring tag)
{
    Glib::ustring tag_remainder = tag;
    list<XmlParameter> parsed_parameters;

    //trim of trailing spaces. There might be a better way to achieve this, but
    //ATM this should do
    while(tag_remainder.at(tag_remainder.length() - 1) == ' ')
    {
        tag_remainder = tag_remainder.substr(0, tag_remainder.length() - 1);
    }

    int spaceIndex = tag_remainder.find(" ");
    int nextSpaceIndex = tag_remainder.find(" ", spaceIndex + 1);


    while(nextSpaceIndex > 0)
    {
        Glib::ustring key_value_pair = tag_remainder.substr(spaceIndex, nextSpaceIndex - spaceIndex);

        XmlParameter parsed_parameter = XmlParameter::parse(key_value_pair);

        if(parsed_parameter.m_key != "" &&
           parsed_parameter.m_value != "")
           {
                parsed_parameters.push_back(XmlParameter(parsed_parameter));
           }

        spaceIndex = nextSpaceIndex;
        nextSpaceIndex = tag_remainder.find(" ", spaceIndex + 1);
    }

    return parsed_parameters;
}
