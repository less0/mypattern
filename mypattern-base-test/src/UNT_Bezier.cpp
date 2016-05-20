#include "UnitTest++.h"
#include "bezier.h"
#include <array>

namespace
{
    TEST(TestBinomialCoefficient)
    {
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(0,0));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(1,0));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(1,1));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(2,0));
        CHECK_EQUAL(2, MyPattern::Base::Bezier::binom(2,1));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(2,2));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(3,0));
        CHECK_EQUAL(3, MyPattern::Base::Bezier::binom(3,1));
        CHECK_EQUAL(3, MyPattern::Base::Bezier::binom(3,2));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(3,3));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(4,0));
        CHECK_EQUAL(4, MyPattern::Base::Bezier::binom(4,1));
        CHECK_EQUAL(6, MyPattern::Base::Bezier::binom(4,2));
        CHECK_EQUAL(4, MyPattern::Base::Bezier::binom(4,3));
        CHECK_EQUAL(1, MyPattern::Base::Bezier::binom(4,4));

        CHECK_EQUAL(0, MyPattern::Base::Bezier::binom(1,4));
        CHECK_EQUAL(0, MyPattern::Base::Bezier::binom(1,2));
    }

    TEST(TestBernsteinPolynome)
    {
        CHECK_CLOSE(.729, MyPattern::Base::Bezier::bernstein(.1, 0, 3), 1e-8);
        CHECK_CLOSE(.512, MyPattern::Base::Bezier::bernstein(.2, 0, 3), 1e-8);
        CHECK_CLOSE(.343, MyPattern::Base::Bezier::bernstein(.3, 0, 3), 1e-8);
        CHECK_CLOSE(.216, MyPattern::Base::Bezier::bernstein(.4, 0, 3), 1e-8);
        CHECK_CLOSE(.125, MyPattern::Base::Bezier::bernstein(.5, 0, 3), 1e-8);
        CHECK_CLOSE(.064, MyPattern::Base::Bezier::bernstein(.6, 0, 3), 1e-8);
        CHECK_CLOSE(.027, MyPattern::Base::Bezier::bernstein(.7, 0, 3), 1e-8);
        CHECK_CLOSE(.008, MyPattern::Base::Bezier::bernstein(.8, 0, 3), 1e-8);
        CHECK_CLOSE(.001, MyPattern::Base::Bezier::bernstein(.9, 0, 3), 1e-8);
        CHECK_CLOSE(.000, MyPattern::Base::Bezier::bernstein(1.0, 0, 3), 1e-8);

        CHECK_CLOSE(.243, MyPattern::Base::Bezier::bernstein(.1, 1, 3), 1e-8);
        CHECK_CLOSE(.384, MyPattern::Base::Bezier::bernstein(.2, 1, 3), 1e-8);
        CHECK_CLOSE(.441, MyPattern::Base::Bezier::bernstein(.3, 1, 3), 1e-8);
        CHECK_CLOSE(.432, MyPattern::Base::Bezier::bernstein(.4, 1, 3), 1e-8);
        CHECK_CLOSE(.375, MyPattern::Base::Bezier::bernstein(.5, 1, 3), 1e-8);
        CHECK_CLOSE(.288, MyPattern::Base::Bezier::bernstein(.6, 1, 3), 1e-8);
        CHECK_CLOSE(.189, MyPattern::Base::Bezier::bernstein(.7, 1, 3), 1e-8);
        CHECK_CLOSE(.096, MyPattern::Base::Bezier::bernstein(.8, 1, 3), 1e-8);
        CHECK_CLOSE(.027, MyPattern::Base::Bezier::bernstein(.9, 1, 3), 1e-8);
        CHECK_CLOSE(.0, MyPattern::Base::Bezier::bernstein(1.0, 1, 3), 1e-8);

        CHECK_CLOSE(.027, MyPattern::Base::Bezier::bernstein(.1, 2, 3), 1e-8);
        CHECK_CLOSE(.096, MyPattern::Base::Bezier::bernstein(.2, 2, 3), 1e-8);
        CHECK_CLOSE(.189, MyPattern::Base::Bezier::bernstein(.3, 2, 3), 1e-8);
        CHECK_CLOSE(.288, MyPattern::Base::Bezier::bernstein(.4, 2, 3), 1e-8);
        CHECK_CLOSE(.375, MyPattern::Base::Bezier::bernstein(.5, 2, 3), 1e-8);
        CHECK_CLOSE(.432, MyPattern::Base::Bezier::bernstein(.6, 2, 3), 1e-8);
        CHECK_CLOSE(.441, MyPattern::Base::Bezier::bernstein(.7, 2, 3), 1e-8);
        CHECK_CLOSE(.384, MyPattern::Base::Bezier::bernstein(.8, 2, 3), 1e-8);
        CHECK_CLOSE(.243, MyPattern::Base::Bezier::bernstein(.9, 2, 3), 1e-8);
        CHECK_CLOSE(.0, MyPattern::Base::Bezier::bernstein(1.0, 2, 3), 1e-8);
    }

    TEST(CreateBezier)
    {
        array<MyPattern::Base::Point,4> a_points;
        a_points[0] = MyPattern::Base::Point(.0, .0);
        a_points[1] = MyPattern::Base::Point(.5, .0);
        a_points[2] = MyPattern::Base::Point(.5, 1.0);
        a_points[3] = MyPattern::Base::Point(1.0, 1.0);


        MyPattern::Base::Bezier bezier(a_points);

        CHECK_CLOSE(.5, bezier.get_coordinate(.5).get_x(), 1e-9);
        CHECK_CLOSE(.5, bezier.get_coordinate(.5).get_y(), 1e-9);
        CHECK_CLOSE(0, bezier.get_coordinate(0).get_x(), 1e-12);
        CHECK_CLOSE(0, bezier.get_coordinate(0).get_y(), 1e-12);
        CHECK_CLOSE(1, bezier.get_coordinate(1).get_x(), 1e-12);
        CHECK_CLOSE(1, bezier.get_coordinate(1).get_y(), 1e-12);
    }

    TEST(TestBezierLength)
    {
        array<MyPattern::Base::Point,4> a_points;
        a_points[0] = MyPattern::Base::Point(.0, .0);
        a_points[1] = MyPattern::Base::Point(1.0, 1.0);
        a_points[2] = MyPattern::Base::Point(0.0, 0.0);
        a_points[3] = MyPattern::Base::Point(1.0, 1.0);

        MyPattern::Base::Bezier bezier(a_points);

        CHECK_CLOSE(std::sqrt(2.0), bezier.get_length(), 1e-5);
    }

    TEST(GetDistanceToBezier)
    {
        array<MyPattern::Base::Point,4> a_points;
        a_points[0] = MyPattern::Base::Point(.0, .0);
        a_points[1] = MyPattern::Base::Point(1.0, 1.0);
        a_points[2] = MyPattern::Base::Point(0.0, 0.0);
        a_points[3] = MyPattern::Base::Point(1.0, 1.0);

        MyPattern::Base::Bezier bezier(a_points);

        // the distance of the bezier is estimated and is only used to determine the users clicks
        // thus the fairly coarse accuracy is sufficient here
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(0,0)), 1e-9);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.1,.1)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.2,.2)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.3,.3)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.4,.4)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.5,.5)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.6,.6)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.7,.7)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.8,.8)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(.9,.9)), 1e-2);
        CHECK_CLOSE(0, bezier.get_distance(MyPattern::Base::Point(1.0,1.0)), 1e-2);
    }
}
