#include "xmlattribute.h"

using namespace MyPattern::Data;

XmlAttribute::XmlAttribute()
{
    //ctor
}

XmlAttribute::XmlAttribute(std::string name, std::string value)
{
    this->m_key = name;
    this->m_value = value;
}

XmlAttribute::XmlAttribute(const XmlAttribute& base)
{
    this->m_key = base.m_key;
    this->m_value = base.m_value;
}

std::string XmlAttribute::get_name()
{
    return std::string(this->m_key);
}

std::string XmlAttribute::get_value()
{
    return this->m_value;
}

XmlAttribute XmlAttribute::parse(std::string key_value_pair)
{
    XmlAttribute result;
    int equalSignIndex = key_value_pair.find("=");

    if(equalSignIndex < 0)
    {
        return XmlAttribute();
    }

    //TODO: Check if the value is placed between "s

    std::string key = key_value_pair.substr(0, equalSignIndex);
    std::string value = key_value_pair.substr(equalSignIndex + 2,
                                                key_value_pair.length() - (equalSignIndex + 2) - 1);

    result.m_key = std::string(key);
    result.m_value = std::string(value);

    return XmlAttribute(result);
}


list<XmlAttribute> XmlAttribute::parse_from_tag(std::string tag)
{
    std::string tag_remainder = tag;
    list<XmlAttribute> parsed_parameters;

    //trim of trailing spaces. There might be a better way to achieve this, but
    //at the moment this should do
    while(tag_remainder.at(tag_remainder.length() - 1) == ' ')
    {
        tag_remainder = tag_remainder.substr(0, tag_remainder.length() - 1);
    }

    std::string search_pattern = "^([A-Za-z]+=\"[A-Za-z0-9 \\. #$]*\")";

    Glib::RefPtr<Glib::Regex> parameterRegex = Glib::Regex::create(search_pattern,
                                                                   (Glib::RegexCompileFlags)0,
                                                                   (Glib::RegexMatchFlags)0);

    unsigned int checkPatternIndex = tag_remainder.find(" ");

    while(checkPatternIndex < tag_remainder.length() && tag_remainder[checkPatternIndex] != '>')
    {
        if(parameterRegex->match(tag_remainder.substr(checkPatternIndex)))
        {
            int endQuoteIndex = tag_remainder.find('"', checkPatternIndex);
            endQuoteIndex = tag_remainder.find('"', ++endQuoteIndex);

            std::string match = tag_remainder.substr(checkPatternIndex,
                                                       endQuoteIndex - checkPatternIndex + 1);

            XmlAttribute parsed_parameter = XmlAttribute::parse(match);
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
