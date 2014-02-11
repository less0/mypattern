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

/*! \brief Abstract base class that represents evaluatable atomic or compound
* terms
*/
class Term
{
    public:
        /*! Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Term& operator=(const Term& other);

        ~Term()
        {}

        /*! \brief Evaluates the term given a list of named values
        */
        virtual double evaluate(map<ustring,double> values) = 0;
        /*! \brief Gets all symbol names of the term
        */
        virtual list<Glib::ustring> get_symbol_names() = 0;

        /*! \brief Parses a formula and returns a ptr to a Term object
        * representing the formula
        */
        static shared_ptr<Term> parse(const ustring &formula);
    protected:
    private:
        static ustring s_operators;
        static ustring s_valid_symbol;
        static ustring s_valid_number;
        static const char s_substituion_marker = '?';

        static shared_ptr<Term> get_left_atomic(ustring formula, int index, const map<ustring, shared_ptr<Term>> &substitutions, int &start_index);
        static shared_ptr<Term> get_right_atomic(ustring formula, int index, const map<ustring, shared_ptr<Term>> &substitutions, int &end_index);

        static shared_ptr<Term> parse_atomic(ustring term, const map<ustring, shared_ptr<Term>> &substitutions);
};



} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_FORMULA_TERM_H
