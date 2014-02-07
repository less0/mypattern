#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_DIFFERENCETERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_DIFFERENCETERM_H

#include <evaluation/formula/term.h>

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class DifferenceTerm : public MyPattern::Base::Evaluation::Formula::Term
{
    public:
        /** Default constructor */
        DifferenceTerm();
        /** Default destructor */
        virtual ~DifferenceTerm();
        /** Copy constructor
         *  \param other Object to copy from
         */
        DifferenceTerm(const DifferenceTerm& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        DifferenceTerm& operator=(const DifferenceTerm& other);
    protected:
    private:
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_DIFFERENCETERM_H
