#include "UnitTest++.h"
#include "evaluation/formula/term.h"
#include <string>
#include <memory>
#include <list>
#include <map>
#include <string>

using namespace std;
using namespace MyPattern::Base::Evaluation::Formula;

namespace
{
    TEST(TestSingleConstantTerm)
    {
        shared_ptr<Term> t = Term::parse("3.14159");
        map<string,double> values;
        CHECK_EQUAL(3.14159, t->evaluate(values));
    }

    TEST(TestSingleScalarTerm)
    {
        shared_ptr<Term> t = Term::parse("#foobar");
        map<string, double> values;
        values.insert(pair<string,double>("#foobar", 123.45));
        CHECK_EQUAL(123.45, t->evaluate(values));
    }

    TEST(TestSimpleAddition)
    {
        shared_ptr<Term> t = Term::parse("#foo+#bar");
        map<string,double> values;
        values.insert(pair<string,double>("#foo", 1.23));
        values.insert(pair<string,double>("#bar", 3.21));
        CHECK_CLOSE(4.44, t->evaluate(values), 1e-6);
    }

    TEST(TestSimpleMultiplication)
    {
        shared_ptr<Term> t = Term::parse("#f*#b");
        map<string,double> values;
        values.insert(pair<string,double>("#f", 1.23));
        values.insert(pair<string,double>("#b", 3.21));
        CHECK_CLOSE(3.9483, t->evaluate(values), 1e-6);
    }

    TEST(TestOperatorOrder)
    {
        shared_ptr<Term> t = Term::parse("#foo*#bar+#foobar");
        map<string,double> values;
        values.insert(pair<string,double>("#foo", 2));
        values.insert(pair<string,double>("#bar", 3));
        values.insert(pair<string,double>("#foobar", 5));
        CHECK_EQUAL(11, t->evaluate(values));
    }

    TEST(TestOperatorOrder2)
    {
        shared_ptr<Term> t = Term::parse("#foobar+#foo*#bar");
        map<string,double> values;
        values.insert(pair<string,double>("#foo", 2));
        values.insert(pair<string,double>("#bar", 3));
        values.insert(pair<string,double>("#foobar", 5));
        CHECK_EQUAL(11, t->evaluate(values));
    }

    TEST(TestSubtractionWithZeroOutcome)
    {
        shared_ptr<Term> t = Term::parse("#bar-#foo");
        map<string,double> values;
        values.insert(pair<string, double>("#bar", 3.141));
        values.insert(pair<string, double>("#foo", 3.141));
        CHECK_EQUAL(0, t->evaluate(values));
    }

    TEST(TestSubtractionWithNegativeOutcome)
    {
        shared_ptr<Term> t = Term::parse("#bar-#foo");
        map<string,double> values;
        values.insert(pair<string, double>("#bar", 3.141));
        values.insert(pair<string, double>("#foo", 4.0));
        CHECK_EQUAL(-0.859, t->evaluate(values));
    }

    TEST(TestSubtractionWithPositiveOutcome)
    {
        shared_ptr<Term> t = Term::parse("#bar-#foo");
        map<string,double> values;
        values.insert(pair<string, double>("#bar", 3.141));
        values.insert(pair<string, double>("#foo", 2.0));
        CHECK_EQUAL(1.141, t->evaluate(values));
    }

    TEST(TestLiteralSubtractionDivisionOperatorOrder)
    {
        shared_ptr<Term> t = Term::parse("3.141-3.141/2");
        map<string, double> values;
        CHECK_CLOSE(3.141-3.141/2.0, t->evaluate(values), 1e-6);
    }

    TEST(TestDivisionWithSameValue)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar");
        map<string,double> values;
        values.insert(pair<string, double>("#bar", 3.141));
        values.insert(pair<string, double>("#foo", 3.141));
        CHECK_EQUAL(1, t->evaluate(values));
    }

    TEST(TestDivisionWithGreaterValue)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar");
        map<string,double> values;
        values.insert(pair<string, double>("#foo", 3.141));
        values.insert(pair<string, double>("#bar", 6.282));
        CHECK_EQUAL(.5, t->evaluate(values));
    }

    TEST(TestDivisionWithSmallerValue)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar");
        map<string,double> values;
        values.insert(pair<string, double>("#foo", 3.141));
        values.insert(pair<string, double>("#bar", 1.5705));
        CHECK_EQUAL(2.0, t->evaluate(values));
    }

    TEST(TestDoubleDivision)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar/#foobar");
        map<string, double> values;
        values.insert(pair<string, double>("#foo", 1));
        values.insert(pair<string, double>("#bar", 2));
        values.insert(pair<string, double>("#foobar", 3));
        CHECK_EQUAL(1.0/2.0/3.0, t->evaluate(values));
    }

    TEST(TestLiteralDivision)
    {
        shared_ptr<Term> t = Term::parse("1234.0/2");
        map<string,double> values;
        CHECK_EQUAL(617, t->evaluate(values));
    }

	TEST(TestLiteralFormulaWithParentheses1)
	{
		shared_ptr<Term> t = Term::parse("123.0*(1+2)");
		map<string,double> values;
		CHECK_CLOSE(123.0*3, t->evaluate(values), 1e-6);
	}

	TEST(TestLiteralFormulaWithParenteses2)
	{
		shared_ptr<Term> t = Term::parse("22/(2+2)");
		map<string,double> values;
		CHECK_CLOSE(5.5, t->evaluate(values), 1e-6);
	}

	TEST(TestLiteralFormulaWithNestedDivisions)
	{
		shared_ptr<Term> t = Term::parse("1/(1/2)");
		map<string,double> values;

		CHECK_CLOSE(2.0, t->evaluate(values), 1e-6);
	}

	TEST(TestSymbolicFormulaWithNestedDivision)
	{
        shared_ptr<Term> t = Term::parse("#foo/(#bar/#foobar)");
        map<string, double> values;
        values.insert(pair<string, double>("#foo", 3.141));
        values.insert(pair<string, double>("#bar", 1));
        values.insert(pair<string, double>("#foobar", 3.141));

        CHECK_CLOSE(3.141*3.141, t->evaluate(values), 1e-6);
	}

    TEST(TestFormulaWithPrecedingMinus)
    {
        shared_ptr<Term> t = Term::parse("-#foo+#bar");
        map<string,double> values;
        values.insert(pair<string,double>("#foo", 1.23));
        values.insert(pair<string,double>("#bar", 3.21));
        CHECK_CLOSE(-1.23+3.21, t->evaluate(values), 1e-6);
    }

    TEST(TestParenthesesWithPrecedingMinus)
    {
        shared_ptr<Term> t = Term::parse("#foobar*(-#foo+#bar)");
        map<string,double> values;
        values.insert(pair<string,double>("#foo", 1.23));
        values.insert(pair<string,double>("#bar", 3.21));
        values.insert(pair<string,double>("#foobar", 123.4));

        CHECK_CLOSE(123.4*(-1.23+3.21), t->evaluate(values), 1e-6);
    }
}
