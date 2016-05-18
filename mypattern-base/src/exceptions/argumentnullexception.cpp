#include "exceptions/argumentnullexception.h"

namespace MyPattern {
namespace Exceptions {

ArgumentNullException::ArgumentNullException(string argument_name) : Exception("Argument " + argument_name + " must not be NULL")
{
    //ctor
}

ArgumentNullException::~ArgumentNullException()
{
    //dtor
}

ArgumentNullException::ArgumentNullException(const ArgumentNullException& other)
{
    //copy ctor
}

ArgumentNullException& ArgumentNullException::operator=(const ArgumentNullException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Exceptions
} // namespace MyPattern
