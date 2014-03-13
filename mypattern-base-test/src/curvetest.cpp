#include "UnitTest++.h"
#include "evaluation/curveevaluationtreenode.h"
#include "bezierdefinition.h"
#include <iostream>

namespace
{
    TEST(TestSetCurveName)
    {
        shared_ptr<MyPattern::Base::BezierDefinition> bezier = shared_ptr<MyPattern::Base::BezierDefinition>(new MyPattern::Base::BezierDefinition());
        bezier->set_name("bezier");

        MyPattern::Base::Evaluation::CurveEvaluationTreeNode node = MyPattern::Base::Evaluation::CurveEvaluationTreeNode(bezier);
        CHECK_EQUAL("$bezier", node.get_prefixed_name());
    }

    TEST(TestSetCurveLandmarks)
    {
        std::list<Glib::ustring> landmark_names;
        landmark_names.push_back("landmark1");
        landmark_names.push_back("landmark2");
        landmark_names.push_back("landmark3");
        landmark_names.push_back("landmark4");

        MyPattern::Base::BezierDefinition bezier = MyPattern::Base::BezierDefinition();
        bezier.set_landmarks(landmark_names);

        std::list<Glib::ustring> landmark_names_from_curve = bezier.get_landmarks();

        CHECK_EQUAL(4, landmark_names_from_curve.size());

        std::list<Glib::ustring>::iterator it = landmark_names_from_curve.begin();

        CHECK_EQUAL("landmark1", *it);
        it++;
        CHECK_EQUAL("landmark2", *it);
        it++;
        CHECK_EQUAL("landmark3", *it);
        it++;
        CHECK_EQUAL("landmark4", *it);
    }

    TEST(TestEvaluateBezierDefinition)
    {
        std::list<Glib::ustring> landmark_names;
        landmark_names.push_back("landmark1");
        landmark_names.push_back("landmark2");
        landmark_names.push_back("landmark3");
        landmark_names.push_back("landmark4");

        std::list<MyPattern::Base::Point> points;
        points.push_back(MyPattern::Base::Point(0.0,0.0));
        points.push_back(MyPattern::Base::Point(0.5,0.0));
        points.push_back(MyPattern::Base::Point(0.5,1.0));
        points.push_back(MyPattern::Base::Point(1.0,1.0));

        std::array<MyPattern::Base::Point,4> base_bezier_points;
        base_bezier_points[0]  = MyPattern::Base::Point(0.0,0.0);
        base_bezier_points[1]  = MyPattern::Base::Point(0.5,0.0);
        base_bezier_points[2]  = MyPattern::Base::Point(0.5,1.0);
        base_bezier_points[3]  = MyPattern::Base::Point(1.0,1.0);

        MyPattern::Base::Bezier base_bezier = MyPattern::Base::Bezier(base_bezier_points);

        MyPattern::Base::BezierDefinition bezier_definition = MyPattern::Base::BezierDefinition();
        bezier_definition.set_name("curve");
        bezier_definition.set_landmarks(landmark_names);
        MyPattern::Base::BezierComplex evaluated_bezier = bezier_definition.get_bezier(points);

        CHECK_EQUAL("curve", evaluated_bezier.get_name());
        MyPattern::Base::Point bezier_evaluated_at_mid_point = evaluated_bezier.get_coordinate(.5);
        CHECK_CLOSE(.5, bezier_evaluated_at_mid_point.get_x(), 1e-9);
        CHECK_CLOSE(.5, bezier_evaluated_at_mid_point.get_y(), 1e-9);

        CHECK_CLOSE(base_bezier.get_length(), evaluated_bezier.get_length(), 1e-6);

    }
}
