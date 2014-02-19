#include "exceptions/objectnametakenevaluationexception.h"

namespace MyPattern {
namespace Exceptions {

ObjectNameTakenEvaluationException::ObjectNameTakenEvaluationException()
{
    //ctor
}

ObjectNameTakenEvaluationException::~ObjectNameTakenEvaluationException()
{
    //dtor
}

ObjectNameTakenEvaluationException::ObjectNameTakenEvaluationException(const ObjectNameTakenEvaluationException& other)
{
    //copy ctor
}

ObjectNameTakenEvaluationException& ObjectNameTakenEvaluationException::operator=(const ObjectNameTakenEvaluationException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Exceptions
} // namespace MyPattern
