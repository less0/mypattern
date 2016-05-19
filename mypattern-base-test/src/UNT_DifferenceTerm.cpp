#include "UnitTest++.h"

#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/differenceterm.h"
#include "evaluation/formula/scalarterm.h"
#include <map>
#include <memory>
#include <string>

using namespace std;
using namespace MyPattern::Base::Evaluation::Formula;

namespace
{
    TEST(TestDifferenceWithConstantValues)
    {
        DifferenceTerm term(shared_ptr<Term>(new ConstantTerm(4.321)), shared_ptr<Term>(new ConstantTerm(1.234)));
        map<string,double> values;

        CHECK_CLOSE(3.0870, term.evaluate(values), 1e-12);
    }

    TEST(TestDifferenceWithScalarValues)
    {
        DifferenceTerm term(shared_ptr<Term>(new ScalarTerm("#fooBar")), shared_ptr<Term>(new ScalarTerm("#barFoo")));
        map<string,double> values;
        values.insert(pair<string, double>("#fooBar", 12.34));
        values.insert(pair<string, double>("#barFoo", 43.21));

        CHECK_CLOSE(-30.87, term.evaluate(values), 1e-12);
    }

    TEST(TestDifferenceWithSameValue)
    {
        DifferenceTerm term(shared_ptr<Term>(new ScalarTerm("#fooBar")), shared_ptr<Term>(new ScalarTerm("#fooBar")));
        map<string,double> values;
        values.insert(pair<string, double>("#fooBar", 12.34));

        CHECK_CLOSE(.0, term.evaluate(values), 1e-12);
    }

    TEST(TestNestedDifferenceTerms)
    {
        DifferenceTerm term(shared_ptr<Term>(new ConstantTerm(1.0)), shared_ptr<Term>(
            new DifferenceTerm(shared_ptr<Term>(new ConstantTerm(0)), shared_ptr<Term>(new ConstantTerm(1)))
            ));
        map<string, double> values;

        CHECK_CLOSE(2, term.evaluate(values), 1e-12);
    }
}
