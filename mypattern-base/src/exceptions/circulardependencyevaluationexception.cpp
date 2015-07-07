#include "exceptions/circulardependencyevaluationexception.h"

namespace MyPattern {
namespace Exceptions {

CircularDependencyEvaluationException::CircularDependencyEvaluationException() : EvaluationException("Circular dependency found")
{
    //ctor
}

CircularDependencyEvaluationException::~CircularDependencyEvaluationException()
{
    //dtor
}

CircularDependencyEvaluationException::CircularDependencyEvaluationException(const CircularDependencyEvaluationException& other)
{
    //copy ctor
}

CircularDependencyEvaluationException& CircularDependencyEvaluationException::operator=(const CircularDependencyEvaluationException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Exceptions
} // namespace MyPattern
