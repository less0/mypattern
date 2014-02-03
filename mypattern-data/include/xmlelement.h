#ifndef MYPATTERN_DATA_XMLELEMENT_H
#define MYPATTERN_DATA_XMLELEMENT_H

#include "exceptions/exception.h"
#include "glibmm/ustring.h"
#include "xmlattribute.h"
#include <memory>
#include <list>

//using namespace MyPattern::Base;
using namespace MyPattern::Exceptions;


namespace MyPattern {
namespace Data {

class XmlElement
{
    public:
        /** Default constructor */
        XmlElement();

        XmlElement(Glib::ustring name, list<XmlAttribute> attributes, bool isEmpty, bool isEndElement);
        /** Default destructor */
        virtual ~XmlElement();
        /** Copy constructor
         *  \param other Object to copy from
         */
        XmlElement(const XmlElement& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        XmlElement& operator=(const XmlElement& other);
        /** Access m_Attributes;
         * \return The current value of m_Attributes;
         */
        list<MyPattern::Data::XmlAttribute> GetAttributes() { return m_Attributes; }

        void AddAttribute(XmlAttribute attribute);
        /** Access m_isEmpty
         * \return The current value of m_isEmpty
         */
        bool isEmpty() { return m_isEmpty; }

        bool isEndElement() { return m_isEndElement; }

        /*! \brief Gets the name of the element */
        Glib::ustring GetName()
        {
            return m_name;
        }

        static XmlElement parse_element(Glib::ustring schema, int start_index, int& end_index);
    protected:
    private:
        list<XmlAttribute> m_Attributes; //!< Member variable "m_Attributes;"
        bool m_isEmpty; //!< Member variable "m_isEmpty"
        bool m_isEndElement;
        Glib::ustring m_name;

        static bool is_valid_name_char(char c);
};

} // namespace Data
} // namespace MyPattern

#endif // MYPATTERN_DATA_XMLELEMENT_H
