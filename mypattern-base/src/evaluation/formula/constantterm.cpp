#include "evaluation/formula/constantterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ConstantTerm::~ConstantTerm()
{

}

ConstantTerm::ConstantTerm(double value)
{
    m_value = value;
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

double ConstantTerm::evaluate(map<Glib::ustring,double>)
{
    return m_value;
}

list<Glib::ustring> ConstantTerm::get_symbol_names()
{
    return list<Glib::ustring>();
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
