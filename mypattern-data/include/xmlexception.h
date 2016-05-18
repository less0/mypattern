#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <string>
#include <exception.h>

namespace MyPattern {
namespace Data {

class XmlException : public MyPattern::Exceptions::Exception
{
    public:
        /*! Default constructor */
        XmlException();
        /*! Constructor with custom message */
        XmlException(std::string message) : Exception(message)
        {}
        /** Default destructor */
        virtual ~XmlException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        XmlException(const XmlException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        XmlException& operator=(const XmlException& other);
    protected:
    private:
};

} // namespace Data
} // namespace MyPattern

#endif // XMLEXCEPTION_H
