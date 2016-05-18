#include "UnitTest++.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/term.h"

using namespace MyPattern::Base::Evaluation::Formula;
using namespace std;

namespace
{
    TEST(TestConstantTerm)
    {
        map<string,double> values;
        shared_ptr<Term> term = shared_ptr<Term>(new ConstantTerm(1.23));
        CHECK_EQUAL(1.23, term->evaluate(values));
    }
}
