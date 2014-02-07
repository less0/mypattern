#include "evaluation/formula/differenceterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

DifferenceTerm::DifferenceTerm()
{
    //ctor
}

DifferenceTerm::~DifferenceTerm()
{
    //dtor
}

DifferenceTerm::DifferenceTerm(const DifferenceTerm& other)
{
    //copy ctor
}

DifferenceTerm& DifferenceTerm::operator=(const DifferenceTerm& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
