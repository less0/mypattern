#include "UnitTest++.h"
#include "evaluation/formula/term.h"
#include <string>
#include <memory>
#include <list>
#include <map>
#include "glibmm/ustring.h"

using namespace std;
using namespace MyPattern::Base::Evaluation::Formula;

namespace
{
//    TEST(TestSimpleAddition)
//    {
//        shared_ptr<Term> t = Term::parse("#foo+#bar");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring,double>("#foo", 1.23));
//        values.insert(pair<Glib::ustring,double>("#bar", 3.21));
//        CHECK_EQUAL(4.44, t->evaluate(values));
//    }
//
//    TEST(TestSimpleMultiplication)
//    {
//        shared_ptr<Term> t = Term::parse("#f*#b");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring,double>("#f", 1.23));
//        values.insert(pair<Glib::ustring,double>("#b", 3.21));
//        CHECK_EQUAL(3.9483, t->evaluate(values));
//    }
//
//    TEST(TestOperatorOrder)
//    {
//        shared_ptr<Term> t = Term::parse("#foo*#bar+#foobar");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring,double>("#foo", 2));
//        values.insert(pair<Glib::ustring,double>("#bar", 3));
//        values.insert(pair<Glib::ustring,double>("#foobar", 5));
//        CHECK_EQUAL(11, t->evaluate(values));
//    }
//
//    TEST(TestOperatoOrder2)
//    {
//        shared_ptr<Term> t = Term::parse("#foobar+#foo*#bar");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring,double>("#foo", 2));
//        values.insert(pair<Glib::ustring,double>("#bar", 3));
//        values.insert(pair<Glib::ustring,double>("#foobar", 5));
//        CHECK_EQUAL(11, t->evaluate(values));
//    }
//
//    TEST(TestSubtractionWithZeroOutcome)
//    {
//        shared_ptr<Term> t = Term::parse("#bar-#foo");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring, double>("#bar", 3.141));
//        values.insert(pair<Glib::ustring, double>("#foo", 3.141));
//        CHECK_EQUAL(0, t->evaluate(values));
//    }
//
//    TEST(TestSubtractionWithNegativeOutcome)
//    {
//        shared_ptr<Term> t = Term::parse("#bar-#foo");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring, double>("#bar", 3.141));
//        values.insert(pair<Glib::ustring, double>("#foo", 4.0));
//        CHECK_EQUAL(-0.859, t->evaluate(values));
//    }
//
//    TEST(TestSubtractionWithPositiveOutcome)
//    {
//        shared_ptr<Term> t = Term::parse("#bar-#foo");
//        map<Glib::ustring,double> values;
//        values.insert(pair<Glib::ustring, double>("#bar", 3.141));
//        values.insert(pair<Glib::ustring, double>("#foo", 2.0));
//        CHECK_EQUAL(1.141, t->evaluate(values));
//    }

    TEST(TestDivisionWithSameValue)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar");
        map<Glib::ustring,double> values;
        values.insert(pair<Glib::ustring, double>("#bar", 3.141));
        values.insert(pair<Glib::ustring, double>("#foo", 3.141));
        CHECK_EQUAL(1, t->evaluate(values));
    }

    TEST(TestDivisionWithGreaterValue)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar");
        map<Glib::ustring,double> values;
        values.insert(pair<Glib::ustring, double>("#bar", 3.141));
        values.insert(pair<Glib::ustring, double>("#foo", 6.282));
        CHECK_EQUAL(.5, t->evaluate(values));
    }

    TEST(TestDivisionWithSmallerValue)
    {
        shared_ptr<Term> t = Term::parse("#foo/#bar");
        map<Glib::ustring,double> values;
        values.insert(pair<Glib::ustring, double>("#bar", 3.141));
        values.insert(pair<Glib::ustring, double>("#foo", 1.5705));
        CHECK_EQUAL(2.0, t->evaluate(values));
    }

}
