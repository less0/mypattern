#include "UnitTest++.h"
#include "point.h"

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

    TEST(MultiplyPointWithDouble)
    {
        MyPattern::Base::Point p(.25,.25);

        p = p * 4;

        CHECK_CLOSE(1, p.get_x(), 1e-9);
        CHECK_CLOSE(1, p.get_y(), 1e-9);
    }
}
