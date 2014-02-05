#include "evaluation/formula/term.h"
#include "glibmm/regex.h"
#include "evaluation/formula/constantterm.h"

#include <map>

using namespace Glib;
using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {
namespace Formula {



Term& Term::operator=(const Term& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

shared_ptr<Term> Term::parse(Glib::ustring definition)
{
    shared_ptr<Term> result = shared_ptr<Term>(new ConstantTerm());
    map<ustring, shared_ptr<Term>> substitutions;

    Glib::ustring measuresPattern = "^#[A-Za-z]{1,1}[A-Za-z0-9]*";
    Glib::ustring landmarkPattern = "^$[A-Za-z]{1,1}";

    return result;
}

} // namespace Formula
} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
