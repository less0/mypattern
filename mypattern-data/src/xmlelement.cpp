#include "xmlelement.h"
#include "xmlexception.h"

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
            std::string regexPattern = "^(\\<\\!\\-\\-\\s[\\w\\s.,\\-]*\\s\\-\\-\\>|</{0,1}([A-Za-z0-9:]+)(\\s([A-Za-z]+=\"[A-Za-z0-9\\.\\s#$]*\"))*(\\s)*/{0,1}>)(.*)";
			
			std::regex rgx(regexPattern);						   
            std::smatch matchinfo;

			if(regex_match(remainder, matchinfo, rgx))
            {
                std::string full_match =  matchinfo.str(1);
                std::string name_match = matchinfo.str(2);

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
