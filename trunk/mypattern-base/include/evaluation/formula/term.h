#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H

#include <list>
#include <map>
#include <string>
#include <memory>
#include <glibmm/ustring.h>

using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

class Term
{
    public:
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Term& operator=(const Term& other);

        ~Term()
        {}

        virtual double evaluate(map<Glib::ustring,double> values) = 0;
        virtual list<Glib::ustring> get_symbol_names() = 0;

        static shared_ptr<Term> parse(Glib::ustring formula);
    protected:
    private:
};

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H
