#include "evaluation/formula/quotientterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

QuotientTerm::QuotientTerm(shared_ptr<Term> divident, shared_ptr<Term> divisor)
{
    m_divident = divident;
    m_divisor = divisor;
}

QuotientTerm::~QuotientTerm()
{
    //dtor
}

double QuotientTerm::evaluate(map<ustring,double> values)
{
    return m_divident->evaluate(values) / m_divisor->evaluate(values);
}

list<ustring> QuotientTerm::get_symbol_names()
{
    list<ustring> result = m_divisor->get_symbol_names();
    list<ustring> divident_symbols = m_divident->get_symbol_names();

    list<ustring>::iterator it = divident_symbols.begin();
    while(it != divident_symbols.end())
    {
        result.push_back(*it);
    }

    return result;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
