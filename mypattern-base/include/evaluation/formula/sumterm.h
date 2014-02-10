#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_SUMTERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_SUMTERM_H

#include <evaluation/formula/term.h>
#include <glibmm/ustring.h>
#include <map>
#include <list>

using namespace Glib;
using namespace std;


namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class SumTerm : public MyPattern::Base::Evaluation::Formula::Term
{
    public:
        /** Default constructor */
        SumTerm(shared_ptr<Term>, shared_ptr<Term>);
        /** Default destructor */
        ~SumTerm();

        double evaluate(map<ustring, double>);
        list<ustring> get_symbol_names();
    protected:
    private:
        shared_ptr<Term> m_summand_1;
        shared_ptr<Term> m_summand_2;
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_SUMTERM_H
