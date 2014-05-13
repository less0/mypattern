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

    TEST(ScalarTermWithParameter)
    {
	map<ustring, double> values;
	values.insert(pair<ustring,double>("$bar[.25]", 1.23));
	shared_ptr<Term> term = shared_ptr<Term>(new ScalarTerm("$bar[.25]"));
	CHECK_EQUAL(1.23, term->evaluate(values));
    }

    TEST(ParseScalarTermWithNumericParameter)
    {
        map<ustring, double> values;
        values.insert(pair<ustring,double>("$bar[.25]", 1.23));
        shared_ptr<Term> term = Term::parse("$bar[.25]");
        CHECK_EQUAL(1.23, term->evaluate(values));
    }

    TEST(ParseScalarTermWithNumericAndCoordinateParameter)
    {
        map<ustring, double> values;
        values.insert(pair<ustring,double>("$bar[.25][X]", 1.23));
        shared_ptr<Term> term = Term::parse("$bar[.25][X]");
        CHECK_EQUAL(1.23, term->evaluate(values));
    }

    TEST(ParseScalarTermWithCoordinateParameter)
    {
        map<ustring, double> values;
        values.insert(pair<ustring,double>("@bar[X]", 6.485));
        shared_ptr<Term> term = Term::parse("@bar[X]");
        CHECK_EQUAL(6.485, term->evaluate(values));
    }
}
