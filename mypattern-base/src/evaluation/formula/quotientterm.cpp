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

double QuotientTerm::evaluate(map<string,double> values)
{
    return m_divident->evaluate(values) / m_divisor->evaluate(values);
}

list<string> QuotientTerm::get_symbol_names()
{
    list<string> result = m_divisor->get_symbol_names();
    list<string> divident_symbols = m_divident->get_symbol_names();

    list<string>::iterator it = divident_symbols.begin();
    while(it != divident_symbols.end())
    {
        result.push_back(*it);
        it++;
    }

    return result;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
