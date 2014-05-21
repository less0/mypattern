#include "evaluation/formula/scalarterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ScalarTerm::ScalarTerm(const ScalarTerm& other)
{
    //copy ctor
    this->m_symbol = other.m_symbol;
}

ScalarTerm::ScalarTerm(string symbol)
{
    m_symbol = symbol;
}

ScalarTerm::~ScalarTerm()
{
}

ScalarTerm& ScalarTerm::operator=(const ScalarTerm& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


double ScalarTerm::evaluate(map<Glib::ustring,double> values)
{
    if(values.count(m_symbol) == 0)
    {
	throw MyPattern::Exceptions::FormulaEvaluationException("Symbol not found");
    }

    return values[m_symbol];
}

list<ustring> ScalarTerm::get_symbol_names()
{
    list<ustring> result;
    result.push_back(m_symbol);
    return result;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
