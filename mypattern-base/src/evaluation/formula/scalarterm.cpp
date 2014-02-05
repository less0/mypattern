#include "evaluation/formula/scalarterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ScalarTerm::ScalarTerm(const ScalarTerm& other)
{
    //copy ctor
}

ScalarTerm& ScalarTerm::operator=(const ScalarTerm& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
