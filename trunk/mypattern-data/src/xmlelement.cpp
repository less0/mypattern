#include "xmlelement.h"
#include "xmlexception.h"

#include "glibmm/regex.h"

namespace MyPattern {
    namespace Data {

        XmlElement::XmlElement()
        {
            //ctor
        }

        XmlElement::XmlElement(Glib::ustring name, list<XmlAttribute> attributes, bool isEmpty, bool isEndElement)
        {
            m_name = name;
            m_Attributes = attributes;
            m_isEmpty = isEmpty;
            m_isEndElement = isEndElement;

            if(isEmpty && isEndElement)
            {
                throw XmlException("Element can't be empty and element at the same time");
            }
        }

        XmlElement::~XmlElement()
        {
            //dtor
        }

        XmlElement::XmlElement(const XmlElement& other)
        {
            //copy ctor
        }

        XmlElement& XmlElement::operator=(const XmlElement& rhs)
        {
            if (this == &rhs) return *this; // handle self assignment
            //assignment operator
            return *this;
        }

        XmlElement XmlElement::parse_element(Glib::ustring schema, int start_index, int& end_index)
        {
            if(schema[start_index] != '<')
            {
                throw XmlException("Parser error");
            }

            Glib::ustring remainder = schema.substr(start_index);
            Glib::ustring regexPattern = "^</{0,1}([A-Za-z0-9:]+)( ([A-Za-u]+=\"[A-Za-z0-9\\. ]*\"))*( )*/{0,1}>";

            Glib::RefPtr<Glib::Regex> elementRegex = Glib::Regex::create(regexPattern,
                                                                   (Glib::RegexCompileFlags)0,
                                                                   (Glib::RegexMatchFlags)0);

            Glib::MatchInfo matchinfo;


            if(elementRegex->match(remainder, matchinfo))
            {
                Glib::ustring full_match =  matchinfo.fetch(0);
                Glib::ustring name_match = matchinfo.fetch(1);

                end_index = start_index + full_match.length() - 1;

                list<XmlAttribute> attributes = XmlAttribute::parse_from_tag(remainder.substr(0, full_match.length()));
                bool isEndElement = full_match[1] == '/';
                bool isEmpty = full_match[full_match.length() - 2] == '/';


                return XmlElement(name_match, attributes, isEmpty, isEndElement);
            }
            else
            {
                throw XmlException("Unexpected ");
            }
        }

    } // namespace Data
} // namespace MyPattern
