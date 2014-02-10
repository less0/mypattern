#include "UnitTest++.h"
#include <map>
#include <list>
#include "evaluation/formula/term.h"
#include "evaluation/formula/constantterm.h"
#include "evaluation/formula/scalarterm.h"
#include "evaluation/formula/sumterm.h"
#include "evaluation/formula/differenceterm.h"

using namespace Glib;
using namespace std;
using namespace MyPattern::Base::Evaluation::Formula;

namespace
{
    TEST(TestSumWithConstantTerms)
    {
        SumTerm term(shared_ptr<Term>(new ConstantTerm(7.234)), shared_ptr<Term>(new ConstantTerm(2.866)));
        map<ustring, double> values;

        CHECK_EQUAL(10.1, term.evaluate(values));
    }

    TEST(TestSumWithScalarTerms)
    {
        SumTerm term(shared_ptr<Term>(new ScalarTerm("#foo")), shared_ptr<Term>(new ScalarTerm("#bar")));
        map<ustring, double> values;
        values.insert(pair<ustring,double>("#bar", 1622.324));
        values.insert(pair<ustring,double>("#foo", 89923.45));

        CHECK_CLOSE(91545.774, term.evaluate(values), 1e-6);
    }

    TEST(TestSumWithNestedDifference)
    {
        SumTerm term(shared_ptr<Term>(new ConstantTerm(3.1415926)),shared_ptr<Term>(new DifferenceTerm(
            shared_ptr<Term>(new ConstantTerm(0)),
            shared_ptr<Term>(new ConstantTerm(3.1415926)))));
        map<ustring, double> values;

        CHECK_EQUAL(0, term.evaluate(values));
    }

    TEST(TestSumTermSymbolNames)
    {
        SumTerm term(shared_ptr<Term>(new ScalarTerm("#foo")), shared_ptr<Term>(new ScalarTerm("#bar")));
        list<ustring> symbol_names = term.get_symbol_names();
        list<ustring>::iterator it = symbol_names.begin();

        CHECK_EQUAL("#foo", *it);
        it++;
        CHECK_EQUAL("#bar", *it);

    }
}
