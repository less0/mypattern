#include "xmlelement.h"
#include "xmlexception.h"

#include "glibmm/regex.h"

namespace MyPattern {
    namespace Data {

        XmlElement::XmlElement()
        {
            //ctor
        }

        XmlElement::XmlElement(Glib::ustring name, list<XmlParameter> attributes, bool isEmpty, bool isEndElement)
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
//            Glib::ustring regexPattern = "^</{0,1}([A-Za-z0-9:]+)( ([A-Za-u]+=\"[A-Za-z0-9\\. ]*\"))*";

            Glib::RefPtr<Glib::Regex> elementRegex = Glib::Regex::create(regexPattern,
                                                                   (Glib::RegexCompileFlags)0,
                                                                   (Glib::RegexMatchFlags)0);

            Glib::MatchInfo matchinfo;


            if(elementRegex->match(remainder, matchinfo))
            {
                Glib::ustring full_match =  matchinfo.fetch(0);
                Glib::ustring name_match = matchinfo.fetch(1);

                end_index = start_index + full_match.length() - 1;

                list<XmlParameter> attributes = XmlParameter::parse_from_tag(remainder.substr(0, full_match.length()));
                bool isEndElement = full_match[1] == '/';
                bool isEmpty = full_match[full_match.length() - 2] == '/';


                return XmlElement(name_match, attributes, isEmpty, isEndElement);
            }
            else
            {
                throw XmlException("Unexpected ");
            }

//            XmlElement result;
//
//            bool inElement = true;
//
//            bool inName = false;
//
//            bool inAttribute = false;
//            bool inAttributeValue = false;
//
//            bool isContentStart = true;
//
//            int current_index = start_index+1;
//            XmlParameter currentAttribute();
//
//            Glib::ustring name = "";
//            bool isEmpty = false;
//
//            while(inElement)
//            {
//                if(inAttributeValue)
//                {
//                    if(schema[current_index] == '"')
//                    {
//                        inAttributeValue = false;
//                    }
//                }
//                else
//                {
//                    switch(schema[current_index])
//                    {
//                        case '>':
//                            if(!inAttributeValue)
//                            {
//                                end_index = current_index;
//                                inElement = false; //leave the looop
//                            }
//
//                            break;
//                        case ' ':
//                            if(inName)
//                            {
//                                inName = false;
//                            }
//                            break;
//                        case '/':
//                            if(!inAttributeValue)
//                            {
//                                if(isContentStart)
//                                {
//                                    isEmpty = true;
//                                }
//                            }
//                            break;
//                        case '"':
//                            if(!inAttribute)
//                            {
//                                throw XmlException("Unexpected \" in XML-element");
//                            }
//
//                            break;
//                        default:
//                            if(isContentStart && is_valid_name_char(schema[current_index]))
//                            {
//                                name += schema[current_index];
//                                inName = true;
//                            }
//                            else if(isContentStart && schema[current_index] == '/')
//                            {
//                                inName = true;
//                                isEmpty = true;
//                            }
//                            else if(isContentStart && !is_valid_name_char(schema[current_index]))
//                            {
//                                //throw an exception
//                                throw XmlException("Unexpected character in element name");
//                            }
//                            else if(inName && is_valid_name_char(schema[current_index]))
//                            {
//                                name += schema[current_index];
//                            }
//                            else if(!inName && !inAttributeValue && is_valid_name_char(schema[current_index]))
//                            {
//                                inAttribute = true;
//                            }
//                    }
//                }
//
//                isContentStart = false;
//                current_index++;
//            }
//
//            return result;
        }

    } // namespace Data
} // namespace MyPattern
