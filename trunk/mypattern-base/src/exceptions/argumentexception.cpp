#include "exceptions/argumentexception.h"

namespace MyPattern {
namespace Exceptions {

ArgumentException::ArgumentException(Glib::ustring argument_name) : Exception("Argument " + argument_name + " must not be NULL")
{
    //ctor
}

ArgumentException::~ArgumentException()
{
    //dtor
}

ArgumentException::ArgumentException(const ArgumentException& other)
{
    //copy ctor
}

ArgumentException& ArgumentException::operator=(const ArgumentException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Exceptions
} // namespace MyPattern
