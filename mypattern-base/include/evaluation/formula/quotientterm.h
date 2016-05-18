#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_QUOTIENTTERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_QUOTIENTTERM_H

#include <evaluation/formula/term.h>
#include <map>
#include <string>


namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class QuotientTerm : public Term
{
    public:
        /** Default constructor */
        QuotientTerm(shared_ptr<Term> divident, shared_ptr<Term> divisor);
        /** Default destructor */
        virtual ~QuotientTerm();

        double evaluate(map<string,double> values);
        list<string> get_symbol_names();
    protected:
    private:
        shared_ptr<Term> m_divident;
        shared_ptr<Term> m_divisor;
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_QUOTIENTTERM_H
