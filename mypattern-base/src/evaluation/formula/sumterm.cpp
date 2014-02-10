#include "evaluation/formula/sumterm.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

SumTerm::SumTerm(shared_ptr<Term> summand_1, shared_ptr<Term> summand_2)
{
    m_summand_1 = summand_1;
    m_summand_2 = summand_2;
}

SumTerm::~SumTerm()
{

}

double SumTerm::evaluate(map<ustring, double> values)
{
    return m_summand_1->evaluate(values) + m_summand_2->evaluate(values);
}

list<ustring> SumTerm::get_symbol_names()
{
    list<ustring> result = m_summand_1->get_symbol_names();
    list<ustring> s2_symbols = m_summand_2->get_symbol_names();

    for(list<ustring>::iterator it = s2_symbols.begin(); it!=s2_symbols.end(); it++)
    {
        result.push_back(*it);
    }

    return result;
}



} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
