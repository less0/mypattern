#include "evaluation/formula/productterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ProductTerm::ProductTerm(shared_ptr<Term> factor1, shared_ptr<Term> factor2)
{
    m_factor_1 = factor1;
    m_factor_2 = factor2;
}


ProductTerm::ProductTerm(const ProductTerm& other)
{
    //copy ctor
}

ProductTerm& ProductTerm::operator=(const ProductTerm& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

double ProductTerm::evaluate(map<ustring,double> values)
{
    return m_factor_1->evaluate(values) * m_factor_2->evaluate(values);
}

list<ustring> ProductTerm::get_symbol_names()
{
    list<ustring> result = m_factor_1->get_symbol_names();
    list<ustring> factor_2_symbols = m_factor_2->get_symbol_names();

    list<ustring>::iterator it = factor_2_symbols.begin();

    while(it != factor_2_symbols.end())
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
