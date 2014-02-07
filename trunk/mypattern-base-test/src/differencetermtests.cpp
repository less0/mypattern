#include "UnitTest++.h"

#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/differenceterm.h"
#include <map>
#include <glibmm/ustring.h>

using namespace std;
using namespace Glib;
using namespace MyPattern::Base::Evaluation::Formula;

namespace
{
    TEST(TestDifferenceWithConstantValues)
    {
        DifferenceTerm term(shared_ptr<Term>(new ConstantTerm(4.321)), shared_ptr<Term>(new ConstantTerm(1.234)));
        map<ustring,double> values;

        CHECK_CLOSE(3087.0, term.evaluate(values), 1e-12);
    }

    TEST(TestDifferenceWithScalarValues)
    {
        DifferenceTerm term(shared_ptr<Term>(new ScalarTerm("#fooBar")), shared_ptr<Term>(new ScalarTerm("#barFoo")));
        map<ustring,double> values;
        values.insert(pair<ustring, double>("#fooBar", 12.34));
        values.insert(pair<ustring, double>("#barFoo", 43.21));

        CHECK_NEAR(-29.13, term.evaluate(values), 1e-12);
    }

    TEST(TestDifferenceWithSameValue)
    {
        DifferenceTerm term(shared_ptr<Term>(new ScalarTerm("#fooBar")), shared_ptr<Term>(new ScalarTerm("#fooBar")));
        map<ustring,double> values;
        values.insert(pair<ustring, double>("#fooBar", 12.34));

        CHECK_NEAR(.0, term.evaluate(values), 1e-12);
    }

    TEST(TestNestedDifferenceTerms)
    {
        DifferenceTerm term(shared_ptr<Term>(new ConstantTerm(1.0)), shared_ptr<Term>(
            new DifferenceTerm(shared_ptr<Term>(new ConstantTerm(0)), shared_ptr<Term>(new ConstantTerm(1)))
            ));
        map<ustring, double> values;

        CHECK_CLOSE(2, term.evaluate(values), 1e-12);
    }
}
