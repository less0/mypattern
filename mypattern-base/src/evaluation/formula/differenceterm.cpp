#include "evaluation/formula/differenceterm.h"
#include <list>

using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

DifferenceTerm::DifferenceTerm(shared_ptr<Term> first, shared_ptr<Term> second)
{
    m_minuent =  first;
    m_subtrahend = second;
}


double DifferenceTerm::evaluate(map<ustring,double> values)
{
    return m_minuent->evaluate(values) - m_subtrahend->evaluate(values);
}

list<ustring> DifferenceTerm::get_symbol_names()
{
    list<ustring> result = m_subtrahend->get_symbol_names();
    list<ustring> minuent_symbols = m_minuent->get_symbol_names();
    list<ustring>::iterator it = minuent_symbols.begin();
    while(it != minuent_symbols.end())
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
