#include "exception.h"

using namespace MyPattern::Exceptions;

Exception::Exception(std::string message)
{
    this->m_message = message;
}


Exception::Exception(const Exception& other)
{
    this->m_message = other.m_message;
    this->m_stacktrace = other.m_stacktrace;
}

Exception& Exception::operator=(const Exception& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    this->m_message = rhs.m_message;
    this->m_stacktrace = rhs.m_stacktrace;

    //assignment operator
    return *this;
}

