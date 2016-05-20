#include "UnitTest++.h"
#include "point.h"

#include <cmath>

namespace
{
    TEST(CreatePointWithValues)
    {
        MyPattern::Base::Point p(3.141, 6.485);

        CHECK_CLOSE(3.141, p.get_x(), 1e-12);
        CHECK_CLOSE(6.485, p.get_y(), 1e-12);
    }

    TEST(AddPoints)
    {
        MyPattern::Base::Point p1(.5, .5);
        MyPattern::Base::Point p2(.25, .25);

        MyPattern::Base::Point sum = p1 + p2;

        CHECK_CLOSE(.75, sum.get_x(), 1e-9);
        CHECK_CLOSE(.75, sum.get_y(), 1e-9);
    }

    TEST(SubtractPoints)
    {
        MyPattern::Base::Point p1(1.0, 1.0);
        MyPattern::Base::Point p2(.7, .5);

        MyPattern::Base::Point diff = p1 - p2;

        CHECK_CLOSE(.3, diff.get_x(), 1e-9);
        CHECK_CLOSE(.5, diff.get_y(), 1e-9);
    }

    TEST(MultiplyPointWithDouble)
    {
        MyPattern::Base::Point p(.25,.25);

        p = p * 4;

        CHECK_CLOSE(1, p.get_x(), 1e-9);
        CHECK_CLOSE(1, p.get_y(), 1e-9);
    }

    TEST(GetPointAbsoluteValue)
    {
        MyPattern::Base::Point p(.1, .1);
        CHECK_CLOSE(std::sqrt(.1*.1+.1*.1), p.abs(), 1e-8);
        p = MyPattern::Base::Point(.3, .3);
        CHECK_CLOSE(std::sqrt(.3*.3+.3*.3), p.abs(), 1e-8);
        p = MyPattern::Base::Point(-1, -1);
        CHECK_CLOSE(std::sqrt(2), p.abs(), 1e-7);
    }
}
