#include "UnitTest++.h"
#include <map>
#include <glibmm/ustring.h>
#include <evaluation/formula/term.h>
#include <evaluation/formula/scalarterm.h>
#include <exceptions/formulaevaluationexception.h>

using namespace MyPattern::Base::Evaluation::Formula;
using namespace MyPattern::Exceptions;
using namespace Glib;
using namespace std;

namespace
{
    TEST(TestScalarTermWithExistingValue)
    {
        map<ustring, double> values;

        values.insert(pair<ustring, double>("#foobar", 3.141));

        shared_ptr<Term> term = shared_ptr<Term>(new ScalarTerm("#foobar"));

        CHECK_EQUAL(3.141, term->evaluate(values));
    }

    TEST(TestScalarTermWithNonexistingValue)
    {

        map<ustring, double> values;

        values.insert(pair<ustring, double>("#foobar", 3.141));

        shared_ptr<Term> term = shared_ptr<Term>(new ScalarTerm("#barfoo"));

        CHECK_THROW(term->evaluate(values), FormulaEvaluationException);
    }
}
