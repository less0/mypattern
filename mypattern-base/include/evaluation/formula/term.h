#ifndef MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H
#define MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H

#include <list>
#include <map>
#include <string>
#include <memory>
#include <glibmm/ustring.h>

using namespace std;
using namespace Glib;

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

        virtual double evaluate(map<ustring,double> values) = 0;
        virtual list<Glib::ustring> get_symbol_names() = 0;

        static shared_ptr<Term> parse(ustring formula);
    protected:
    private:
        static ustring s_operators;
        static ustring s_valid_symbol;
        static ustring s_valid_number;
        static const char s_substituion_marker = '?';

        static shared_ptr<Term> get_left_atomic(const ustring &formula, int index, const map<ustring, shared_ptr<Term>> &substitutions, int &start_index)
        { return shared_ptr<Term>();}
        static shared_ptr<Term> get_right_atomic(const ustring &formula, int index, const map<ustring, shared_ptr<Term>> &substitutions, int &end_index)
        { return shared_ptr<Term>();}
};



} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H
