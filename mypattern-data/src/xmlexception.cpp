#include "xmlexception.h"

namespace MyPattern {
namespace Data {

XmlException::XmlException()
{
    //ctor
}

XmlException::~XmlException()
{
    //dtor
}

XmlException::XmlException(const XmlException& other)
{
    //copy ctor
}

XmlException& XmlException::operator=(const XmlException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Data
} // namespace MyPattern
