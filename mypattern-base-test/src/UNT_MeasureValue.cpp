#include "UnitTest++.h"
#include "mypattern-base.h"

using namespace MyPattern::Base;

namespace
{

    TEST(TestCreateMeasureValue)
    {
        MeasureValue mv("mv1", "Just a measure value", 1.234);

        CHECK_EQUAL("mv1", mv.get_name());
        CHECK_EQUAL("Just a measure value", mv.get_description());
        CHECK_EQUAL(1.234, mv.get_value());
    }

    TEST(TestAssignValue)
    {
        MeasureValue mv("mv1", "...", 3.141);

        CHECK_EQUAL(3.141,mv.get_value());
        mv.set_value(20.0188);
        CHECK_EQUAL(20.0188, mv.get_value());
    }

    TEST(CopyMeasureValue)
    {
        MeasureValue mv("mvX", "...", 6.0485);

        CHECK_EQUAL("mvX", mv.get_name());
        CHECK_EQUAL("...", mv.get_description());
        CHECK_EQUAL(6.0485, mv.get_value());

        mv.set_value(1.111);

        MeasureValue mv_c(mv);

        CHECK_EQUAL("mvX", mv_c.get_name());
        CHECK_EQUAL("...", mv_c.get_description());
        CHECK_EQUAL(1.111, mv_c.get_value());
    }
}
