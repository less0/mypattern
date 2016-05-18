#include "UnitTest++.h"
#include "evaluation/formula/productterm.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/scalarterm.h"


using namespace MyPattern::Base::Evaluation::Formula;
using namespace std;

namespace
{
    TEST(TestProductTermWithConstantValues)
    {
        ProductTerm term(shared_ptr<Term>(new ConstantTerm(1.11)), shared_ptr<Term>(new ConstantTerm(1.11)));
        map<string,double> values;

        CHECK_CLOSE(1.2321, term.evaluate(values), 1e-12);
    }

    TEST(TestProductTermWithSymbolicValues)
    {
        ProductTerm term(shared_ptr<Term>(new ScalarTerm("#f00")), shared_ptr<Term>(new ScalarTerm("#b4r")));
        map<string, double> values;
        values.insert(pair<string,double>("#f00", 3.141));
        values.insert(pair<string,double>("#b4r", 2.0));
        CHECK_CLOSE(6.282, term.evaluate(values), 1e-12);
    }
}
