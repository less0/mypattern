#include "UnitTest++.h"
#include "evaluation/formula/quotientterm.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/scalarterm.h"

using namespace MyPattern::Base::Evaluation::Formula;
using namespace std;

namespace
{
    TEST(TestQuotientTermWithConstantValues)
    {
        shared_ptr<Term> term = shared_ptr<Term>(new QuotientTerm(shared_ptr<Term>(new ConstantTerm(1.2)), shared_ptr<Term>(new ConstantTerm(2.4))));
        map<string,double> values;

        CHECK_EQUAL(.5, term->evaluate(values));
    }

    TEST(TestQuotientTermWithSymbolicValues)
    {
        QuotientTerm term(shared_ptr<Term>(new ScalarTerm("#foo")), shared_ptr<Term>(new ScalarTerm("#bar")));
        map<string,double> values;
        values.insert(pair<string, double>("#foo", 1.2321));
        values.insert(pair<string, double>("#bar", 1.11));

        CHECK_CLOSE(1.11, term.evaluate(values), 1e-6);
    }

    TEST(TestNestedQuotientTerm)
    {
        QuotientTerm term(shared_ptr<Term>(new ConstantTerm(1.23)), shared_ptr<Term>(new QuotientTerm(shared_ptr<Term>(new ConstantTerm(1.0)), shared_ptr<Term>(new ConstantTerm(2.0)))));
        map<string, double> values;
        CHECK_EQUAL(2.46, term.evaluate(values));
    }
}
