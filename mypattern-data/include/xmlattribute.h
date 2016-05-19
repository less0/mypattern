#ifndef XMLPARAMETER_H
#define XMLPARAMETER_H

#include <string>
#include <list>

using namespace std;

namespace MyPattern
{
    namespace Data
    {
        /** \brief Represents a parameter, consisting of a name and a value, of
         * an XmlNode
         *
         * XML-Tags are basically following the schema <node_name
         * param1="value1" param2="value2"></node_name> (or <node_name
         * param1="value1" param2="value2" /> with an arbitrary number of
         * parameters, each with a name and a value. This class parses a tags
         * parameter and stores it.
         */
        class XmlAttribute
        {
            public:
                XmlAttribute();
                XmlAttribute(std::string name, std::string value);
                XmlAttribute(const XmlAttribute& parameter);
                /** \brief Gets the name of the parameter
                *
                */
                std::string get_name();
                void set_name(std::string);
                std::string get_value();
                void set_value(std::string);
                /** \brief Parses a list of XmlAttribute objects from a valid
                * XML-Tag.
                *
                * This function takes an XML-tag and searches key-value-pairs
                * in the format key="value" in the tag. Please note, that
                * escaped strings are NOT considered at the moment, therefor
                * a key-value-pair like key="value \"stuff\"" will actually find
                * the key 'key' and the value 'value \', the part after the
                * quotation mark will be ignored, because it does not match the
                * expected key-value-pair format
                *
                */
                static list<XmlAttribute> parse_from_tag(std::string tag);
                /** \brief Parses a key-value-pair as given in the XML-tag.
                *
                * This function takes a key-value-pair in the form key="value"
                * and creates a new XmlAttribute with the corresponding key and
                * value.
                */
                static XmlAttribute parse(std::string key_value_pair);
            protected:
            private:
                std::string m_key;
                std::string m_value;
        };
    }
}


#endif // XMLPARAMETER_H
