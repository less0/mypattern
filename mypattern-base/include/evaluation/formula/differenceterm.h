#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_DIFFERENCETERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_DIFFERENCETERM_H

#include <evaluation/formula/term.h>
#include <memory>
#include <map>
#include <string>

using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class DifferenceTerm : public MyPattern::Base::Evaluation::Formula::Term
{
    public:
        /** Default constructor */
        DifferenceTerm(shared_ptr<Term>,shared_ptr<Term>);
        /** Default destructor */
        virtual ~DifferenceTerm() {};
        double evaluate(map<string, double>);
        list<string> get_symbol_names();
    protected:
    private:
        shared_ptr<Term> m_subtrahend;
        shared_ptr<Term> m_minuent;
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_DIFFERENCETERM_H
