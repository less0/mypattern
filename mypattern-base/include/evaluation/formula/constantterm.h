#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_CONSTANTTERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_CONSTANTTERM_H

#include <evaluation/formula/term.h>
#include <list>
#include <string>

using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class ConstantTerm : public MyPattern::Base::Evaluation::Formula::Term
{
    public:
        /** Default constructor */
        ConstantTerm(double value);
        /** Default destructor */
        virtual ~ConstantTerm();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ConstantTerm(const ConstantTerm& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ConstantTerm& operator=(const ConstantTerm& other);

        double evaluate(map<string,double>);

        list<string> get_symbol_names();
    protected:
    private:
        double m_value;
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_CONSTANTTERM_H
