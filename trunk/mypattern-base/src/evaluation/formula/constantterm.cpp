#include "evaluation/formula/constantterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ConstantTerm::~ConstantTerm()
{

}

ConstantTerm::ConstantTerm(const ConstantTerm& other)
{
    //copy ctor
}

ConstantTerm& ConstantTerm::operator=(const ConstantTerm& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
