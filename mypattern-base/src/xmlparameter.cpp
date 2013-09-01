#include "xmlparameter.h"

XmlParameter::XmlParameter()
{
    //ctor
}

XmlParameter::XmlParameter(Glib::ustring name, Glib::ustring value)
{
    this->m_key = name;
    this->m_value = value;
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

    //TODO: Check if the value is placed between "s

    Glib::ustring key = key_value_pair.substr(0, equalSignIndex);
    Glib::ustring value = key_value_pair.substr(equalSignIndex + 2,
                                                key_value_pair.length() - (equalSignIndex + 2) - 1);

    result.m_key = Glib::ustring(key);
    result.m_value = Glib::ustring(value);

    return XmlParameter(result);
}


list<XmlParameter> XmlParameter::parse_from_tag(Glib::ustring tag)
{
    Glib::ustring tag_remainder = tag;
    list<XmlParameter> parsed_parameters;

    //trim of trailing spaces. There might be a better way to achieve this, but
    //at the moment this should do
    while(tag_remainder.at(tag_remainder.length() - 1) == ' ')
    {
        tag_remainder = tag_remainder.substr(0, tag_remainder.length() - 1);
    }

    Glib::ustring search_pattern = "^([A-Za-u]+=\"[A-Za-z0-9 ]+\")";

    Glib::RefPtr<Glib::Regex> parameterRegex = Glib::Regex::create(search_pattern,
                                                                   (Glib::RegexCompileFlags)0,
                                                                   (Glib::RegexMatchFlags)0);

    int checkPatternIndex = tag_remainder.find(" ");

    while(checkPatternIndex < tag_remainder.length() && tag_remainder[checkPatternIndex] != '>')
    {
        if(parameterRegex->match(tag_remainder.substr(checkPatternIndex)))
        {
            int endQuoteIndex = tag_remainder.find('"', checkPatternIndex);
            endQuoteIndex = tag_remainder.find('"', ++endQuoteIndex);

            Glib::ustring match = tag_remainder.substr(checkPatternIndex,
                                                       endQuoteIndex - checkPatternIndex + 1);

            XmlParameter parsed_parameter = XmlParameter::parse(match);
            parsed_parameters.push_back(parsed_parameter);

            checkPatternIndex = endQuoteIndex + 1;
        }
        else
        {
            checkPatternIndex++;
        }
    }

    return parsed_parameters;
}
