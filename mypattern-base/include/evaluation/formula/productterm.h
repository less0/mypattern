#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_PRODUCTTERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_PRODUCTTERM_H

#include <evaluation/formula/term.h>
#include <memory>
#include <list>
#include <glibmm/ustring.h>

using namespace std;
using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class ProductTerm : public MyPattern::Base::Evaluation::Formula::Term
{
    public:
        /** Default constructor */
        ProductTerm(shared_ptr<Term>, shared_ptr<Term>);
        /** Default destructor */
        virtual ~ProductTerm() {}
        /** Copy constructor
         *  \param other Object to copy from
         */
        ProductTerm(const ProductTerm& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ProductTerm& operator=(const ProductTerm& other);

        double evaluate(map<ustring,double> values);
        list<ustring> get_symbol_names();
    protected:
    private:
        shared_ptr<Term> m_factor_1;
        shared_ptr<Term> m_factor_2;
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_PRODUCTTERM_H
