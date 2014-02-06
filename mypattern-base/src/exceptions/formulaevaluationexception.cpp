#include "exceptions/formulaevaluationexception.h"

namespace MyPattern {
namespace Exceptions {

FormulaEvaluationException::FormulaEvaluationException(ustring message) : Exception(message)
{
}

FormulaEvaluationException::~FormulaEvaluationException()
{
    //dtor
}

FormulaEvaluationException::FormulaEvaluationException(const FormulaEvaluationException& other)
{
    //copy ctor
}

FormulaEvaluationException& FormulaEvaluationException::operator=(const FormulaEvaluationException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Exceptions
} // namespace MyPattern
