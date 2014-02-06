#include "evaluation/formula/term.h"
#include "glibmm/regex.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/quotientterm.h"

#include <map>
#include <sstream>

using namespace Glib;
using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {

ustring Term::s_operators = "/*-+";
ustring Term::s_valid_symbol = "^[@$#?]{1,1}[A-Za-z0-9](\[([XY]{1,1}|(1\.[0]{1,})|0.[0-9]{1,})\]){0,1}$";
ustring Term::s_valid_number = "^([0-9]+|[0-9]{0,}\.[0-9]{1,}$";

Term& Term::operator=(const Term& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

shared_ptr<Term> Term::parse(Glib::ustring formula)
{
    shared_ptr<Term> result = shared_ptr<Term>(new ConstantTerm(.0));
    map<ustring, shared_ptr<Term>> substitutions;
    int substitution_index = 0;

    Glib::ustring measuresPattern = "^#[A-Za-z]{1,1}[A-Za-z0-9]*";
    Glib::ustring landmarkPattern = "^$[A-Za-z]{1,1}";

    int operator_index = 0;
    int start_index = 0;
    int end_index = 0;

    return shared_ptr<Term>(new ConstantTerm(.0));

    while((operator_index = formula.find('/')) > 0)
    {
        shared_ptr<Term> left_atomic = Term::get_left_atomic(formula, operator_index, substitutions, start_index);
        shared_ptr<Term> right_atomic = Term::get_right_atomic(formula, operator_index, substitutions, end_index);

        shared_ptr<Term> substituted_term = shared_ptr<Term>(new QuotientTerm(left_atomic, right_atomic));

        stringstream s;
        s << s_substituion_marker <<  substitution_index++;

        formula.erase(start_index, (end_index - start_index));
        formula.insert(start_index, s.str());

        substitutions.insert(pair<ustring,shared_ptr<Term>>(s.str(), substituted_term));
    }

    while(formula.find('*'))
    {

    }



    return result;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
