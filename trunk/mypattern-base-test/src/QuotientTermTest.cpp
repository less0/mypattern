#include "UnitTest++.h"
#include "evaluation/formula/quotientterm.h"
#include "evaluation/formula/constantterm.h"


using namespace MyPattern::Base::Evaluation::Formula;

namespace
{
    TEST(TestQuotientTermWithConstantValues)
    {
        shared_ptr<Term> term = shared_ptr<Term>(new QuotientTerm(shared_ptr<Term>(new ConstantTerm(1.2)), shared_ptr<Term>(new ConstantTerm(2.4))));
        map<ustring,double> values;

        CHECK_EQUAL(.5, term->evaluate(values));
    }
}
