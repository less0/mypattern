#include "exceptions/evaluationexception.h"

namespace MyPattern {
namespace Exceptions {

EvaluationException::EvaluationException()
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
