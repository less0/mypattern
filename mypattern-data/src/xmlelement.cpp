#include "xmlelement.h"
#include "xmlexception.h"

#include "glibmm/regex.h"
#include <regex>

#include <iostream>

namespace MyPattern {
    namespace Data {

        XmlElement::XmlElement()
        {
            //ctor
        }

        XmlElement::XmlElement(std::string name, list<XmlAttribute> attributes, bool isEmpty, bool isEndElement, bool isComment)
        {
            m_name = name;
            m_Attributes = attributes;
            m_isEmpty = isEmpty;
            m_isEndElement = isEndElement;
			m_isComment = isComment;

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

        XmlElement XmlElement::parse_element(std::string schema, int start_index, int& end_index)
        {
            if(schema[start_index] != '<')
            {
                throw XmlException("Parser error");
            }
			

            std::string remainder = schema.substr(start_index);
            std::string regexPattern = "^(<!-- [\\w\\s.,\\-\\S]* -->|</{0,1}([A-Za-z0-9:]+)( ([A-Za-z]+=\"[A-Za-z0-9\\. #$]*\"))*( )*/{0,1}>)";
			
            Glib::RefPtr<Glib::Regex> elementRegex = Glib::Regex::create(regexPattern,
                                                                   (Glib::RegexCompileFlags)0,
                                                                   (Glib::RegexMatchFlags)0);

																   
            Glib::MatchInfo matchinfo;


            if(elementRegex->match(remainder, matchinfo))
            {
                std::string full_match =  matchinfo.fetch(0);
                std::string name_match = matchinfo.fetch(2);

                end_index = start_index + full_match.length() - 1;

                list<XmlAttribute> attributes = XmlAttribute::parse_from_tag(remainder.substr(0, full_match.length()));
                bool isEndElement = full_match[1] == '/';
                bool isEmpty = full_match[full_match.length() - 2] == '/';
				bool isComment = full_match[1] == '!' 
					&& full_match[2] == '-' 
					&& full_match[3] == '-';

                return XmlElement(name_match, attributes, isEmpty, isEndElement, isComment);
            }
            else
            {
                throw XmlException("Unexpected " + remainder);
            }
        }

    } // namespace Data
} // namespace MyPattern
