#include "exceptions/evaluationexception.h"

namespace MyPattern {
namespace Exceptions {

EvaluationException::EvaluationException(ustring message) : Exception(message)
{
    //ctor
}

EvaluationException::EvaluationException() : Exception("Evaluation exception")
{
    //ctor
}

EvaluationException::~EvaluationException()
{
    //dtor
}

EvaluationException::EvaluationException(const EvaluationException& other)
{
    //copy ctor
}

EvaluationException& EvaluationException::operator=(const EvaluationException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Exceptions
} // namespace MyPattern
