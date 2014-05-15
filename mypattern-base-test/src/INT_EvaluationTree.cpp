#include "UnitTest++.h"
#include "mypattern-base.h"
#include <iostream>

using namespace MyPattern::Base;
using namespace MyPattern::Base::Evaluation;
using namespace MyPattern::Exceptions;

namespace
{
    TEST(AddLandmarkToTree)
    {
        EvaluationRoot root = EvaluationRoot();
        shared_ptr<PatternObject> landmark = shared_ptr<PatternObject>(new Landmark());


        shared_ptr<EvaluationTreeNode> node =  root.add_object(landmark);
        CHECK_EQUAL(true, node != NULL);
    }

    TEST(AddLandmarkToTreeAndCast)
    {
        EvaluationRoot root = EvaluationRoot();
        shared_ptr<PatternObject> landmark = shared_ptr<PatternObject>(new Landmark());

        shared_ptr<EvaluationTreeNode> node = root.add_object(landmark);
        CHECK_EQUAL(true, dynamic_pointer_cast<LandmarkEvaluationTreeNode>(node) != NULL);
    }

    TEST(AddLandmarkWithExistingName)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
        landmark1->set_name("LM1");
        shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());
        landmark2->set_name("LM1");

        landmark1->get_name();

        CHECK_EQUAL("LM1", landmark1->get_name());
        CHECK_EQUAL("LM1", landmark2->get_name());

        root.add_object(landmark1);
        CHECK_THROW(root.add_object(landmark2), MyPattern::Exceptions::ObjectNameTakenEvaluationException);
    }

    TEST(AddLandmarkWithUnmetDependencies)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("landmark");
        landmark->set_definition_x("@landmark2[X]");

        CHECK_THROW(root.add_object(landmark), MyPattern::Exceptions::UnmetDependenciesEvaluationException);
    }

    TEST(CheckSelfReferringLandmark)
    {
        EvaluationRoot root = EvaluationRoot();
        shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
        landmark1->set_name("lm1");
        landmark1->set_definition_x("@lm1[X]");

        CHECK_THROW(root.add_object(landmark1), MyPattern::Exceptions::UnmetDependenciesEvaluationException);
    }

    TEST(CheckLandmarksNodes)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
        landmark1->set_name("landmark1");

        shared_ptr<EvaluationTreeNode> landmark1_node = root.add_object(landmark1);

        shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());
        landmark2->set_name("landmark2");
        landmark2->set_definition_x("@landmark1[X]+2");
        landmark2->set_definition_y("@landmark1[Y]+2");

        shared_ptr<EvaluationTreeNode> landmark2_node = root.add_object(landmark2);

        list<shared_ptr<EvaluationTreeNode>> landmark2_deps = landmark2_node->get_nodes();

        CHECK_EQUAL(1, landmark2_deps.size());

        list<shared_ptr<EvaluationTreeNode>>::iterator it_deps = landmark2_deps.begin();

        CHECK_EQUAL(*it_deps, landmark1_node);
    }



    TEST(ChangeLandmarkDefinitionY)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
        shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());

        landmark1->set_name("lm1");

        landmark2->set_name("lm2");
        landmark2->set_definition_y("@lm1[X]");

        root.add_object(landmark1);
        shared_ptr<EvaluationTreeNode> lm2_node = root.add_object(landmark2);
        list<shared_ptr<EvaluationTreeNode>> lm2_deps = lm2_node->get_nodes();

        CHECK_EQUAL(1, lm2_deps.size());

        landmark2->set_definition_y("0");

        lm2_deps = lm2_node->get_nodes();
        CHECK_EQUAL(0, lm2_deps.size());
    }

    TEST(ChangeLandmarkDefinitionX)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
        shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());

        landmark1->set_name("lm1");

        landmark2->set_name("lm2");
        landmark2->set_definition_x("@lm1[X]");

        root.add_object(landmark1);
        shared_ptr<EvaluationTreeNode> lm2_node = root.add_object(landmark2);
        list<shared_ptr<EvaluationTreeNode>> lm2_deps = lm2_node->get_nodes();

        CHECK_EQUAL(1, lm2_deps.size());

        landmark2->set_definition_x("0");

        lm2_deps = lm2_node->get_nodes();
        CHECK_EQUAL(0, lm2_deps.size());
    }

	TEST(EvaluateLandmarkPositionWhenAdded)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
		shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());

		landmark1->set_name("lm1");

		landmark2->set_name("lm2");
		landmark2->set_definition_x("@lm1[X]+0.5");
		landmark2->set_definition_y("@lm1[Y]+0.5");

		root.add_object(landmark1);
		shared_ptr<LandmarkEvaluationTreeNode> landmark2_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(landmark2));
		Point landmark2_point = landmark2_node->get_value();

		CHECK_CLOSE(.5, landmark2_point.get_x(), 1e-12);
		CHECK_CLOSE(.5, landmark2_point.get_y(), 1e-12);
	}

	TEST(EvaluateLandmarkPositionAfterChange)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
		shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());

		landmark1->set_name("lm1");
		landmark2->set_name("lm2");

		root.add_object(landmark1);
		shared_ptr<LandmarkEvaluationTreeNode> landmark2_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(landmark2));

		Point landmark2_point = landmark2_node->get_value();

		CHECK_CLOSE(.0, landmark2_point.get_x(), 1e-12);
		CHECK_CLOSE(.0, landmark2_point.get_y(), 1e-12);


		landmark2->set_definition_x("@lm1[X]+3.141");
		landmark2->set_definition_y("@lm1[Y]+6.282");

		landmark2_point = landmark2_node->get_value();

		CHECK_CLOSE(3.141, landmark2_point.get_x(), 1e-6);
		CHECK_CLOSE(6.282, landmark2_point.get_y(), 1e-6);
	}

	TEST(EvaluateDependentLandmark)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> landmark1 = shared_ptr<Landmark>(new Landmark());
		shared_ptr<Landmark> landmark2 = shared_ptr<Landmark>(new Landmark());

		landmark1->set_name("lm1");

		landmark2->set_name("lm2");
		landmark2->set_definition_x("@lm1[X]+0.5");
		landmark2->set_definition_y("@lm1[Y]+0.5");

		shared_ptr<LandmarkEvaluationTreeNode> landmark1_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(landmark1));
		shared_ptr<LandmarkEvaluationTreeNode> landmark2_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(landmark2));
		Point landmark2_point = landmark2_node->get_value();

		CHECK_CLOSE(.5, landmark2_point.get_x(), 1e-12);
		CHECK_CLOSE(.5, landmark2_point.get_y(), 1e-12);

		landmark1->set_definition_x("1.0");
		landmark1->set_definition_y("1.0");

		Point landmark1_point = landmark1_node->get_value();

		CHECK_CLOSE(1.0, landmark1_point.get_x(), 1e-12);
		CHECK_CLOSE(1.0, landmark1_point.get_y(), 1e-12);

		landmark2_point = landmark2_node->get_value();

		CHECK_CLOSE(1.5, landmark2_point.get_x(), 1e-9);
		CHECK_CLOSE(1.5, landmark2_point.get_y(), 1e-9);

	}

	TEST(AddCurveToEvaluationRoot)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("foo");
		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("bar");
		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("baz");
		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("qux");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<BezierDefinition> bezier = shared_ptr<BezierDefinition>(new BezierDefinition());

		list<ustring> dependency_names;
		dependency_names.push_back("foo");
		dependency_names.push_back("bar");
		dependency_names.push_back("baz");
		dependency_names.push_back("qux");

		bezier->set_landmarks(dependency_names);
		bezier->set_name("bezier1");

		shared_ptr<CurveEvaluationTreeNode> bezier_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));

		CHECK_EQUAL(true, bezier_node != NULL);
	}

	TEST(AddBezierCurveToEvaluationRootAndGetName)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("foo");
		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("bar");
		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("baz");
		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("qux");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<BezierDefinition> bezier = shared_ptr<BezierDefinition>(new BezierDefinition());

		list<ustring> dependency_names;
		dependency_names.push_back("foo");
		dependency_names.push_back("bar");
		dependency_names.push_back("baz");
		dependency_names.push_back("qux");

		bezier->set_landmarks(dependency_names);

		bezier->set_name("bezier1");

		shared_ptr<CurveEvaluationTreeNode> bezier_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));

		CHECK_EQUAL("$bezier1", bezier_node->get_prefixed_name());

	}

	TEST(AddBezierCurveToEvaluationRootAndGetDependencyNames)
	{

		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("foo");
		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("bar");
		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("baz");
		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("qux");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<BezierDefinition> bezier = shared_ptr<BezierDefinition>(new BezierDefinition());

		bezier->set_name("bezier1");

		list<ustring> dependency_names;
		dependency_names.push_back("foo");
		dependency_names.push_back("bar");
		dependency_names.push_back("baz");
		dependency_names.push_back("qux");

		bezier->set_landmarks(dependency_names);

		shared_ptr<CurveEvaluationTreeNode> bezier_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));

		list<ustring> deps_from_node = bezier_node->depends_on();

		CHECK_EQUAL(4, deps_from_node.size());

		list<ustring>::iterator it = deps_from_node.begin();

		CHECK_EQUAL("@foo", *it);
		it++;
		CHECK_EQUAL("@bar", *it);
		it++;
		CHECK_EQUAL("@baz", *it);
		it++;
		CHECK_EQUAL("@qux", *it);
	}

	TEST(AddCurveWithUnmetDependencies)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<BezierDefinition> bezier = shared_ptr<BezierDefinition>(new BezierDefinition());

		bezier->set_name("bezier1");

		list<ustring> dependency_names;
		dependency_names.push_back("foo");
		dependency_names.push_back("bar");
		dependency_names.push_back("baz");
		dependency_names.push_back("qux");

		bezier->set_landmarks(dependency_names);

		CHECK_THROW(root.add_object(bezier), MyPattern::Exceptions::UnmetDependenciesEvaluationException);
	}

	TEST(AddCurveWithExistingName)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("foo");
		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("bar");
		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("baz");
		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("qux");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<BezierDefinition> bezier1 = shared_ptr<BezierDefinition>(new BezierDefinition());
		shared_ptr<BezierDefinition> bezier2 = shared_ptr<BezierDefinition>(new BezierDefinition());

		bezier1->set_name("bezier1");
		bezier2->set_name("bezier1");

		list<ustring> dependency_names;
		dependency_names.push_back("foo");
		dependency_names.push_back("bar");
		dependency_names.push_back("baz");
		dependency_names.push_back("qux");

		bezier1->set_landmarks(dependency_names);
		bezier2->set_landmarks(dependency_names);

		root.add_object(bezier1);
		CHECK_THROW(root.add_object(bezier2), MyPattern::Exceptions::ObjectNameTakenEvaluationException);
	}

	TEST(GetAddedCurveEvaluatedValue)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("lm1");
		lm1->set_definition_x("0");
		lm1->set_definition_y("0");

		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("lm2");
		lm2->set_definition_x("1");
		lm2->set_definition_y("1");

		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("lm3");
		lm3->set_definition_x("0");
		lm3->set_definition_y("0");

		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("lm4");
		lm4->set_definition_x("1");
		lm4->set_definition_y("1");

		list<ustring> landmark_names;
		landmark_names.push_back("lm1");
		landmark_names.push_back("lm2");
		landmark_names.push_back("lm3");
		landmark_names.push_back("lm4");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<CurveDefinition> bezier = shared_ptr<CurveDefinition>(new BezierDefinition);
		bezier->set_name("bezier1");
		bezier->set_landmarks(landmark_names);
		shared_ptr<CurveEvaluationTreeNode> bezier_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));

		BezierComplex evaluated_bezier = bezier_node->get_value();
		CHECK_CLOSE(.0, evaluated_bezier.get_coordinate(.0).get_x(), 1e-6);
		CHECK_CLOSE(.0, evaluated_bezier.get_coordinate(.0).get_y(), 1e-6);
		CHECK_CLOSE(.5, evaluated_bezier.get_coordinate(.5).get_x(), 1e-6);
		CHECK_CLOSE(.5, evaluated_bezier.get_coordinate(.5).get_y(), 1e-6);
		CHECK_CLOSE(1.0, evaluated_bezier.get_coordinate(1.0).get_x(), 1e-6);
		CHECK_CLOSE(1.0, evaluated_bezier.get_coordinate(1.0).get_y(), 1e-6);
	}

	// Adds a curve to the evaluation root and changes its landmarks afterwards
	// the curve is supposed to be updated
	TEST(GetModifiedCurveEvaluatedValue)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("lm1");
		lm1->set_definition_x("0");
		lm1->set_definition_y("0");

		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("lm2");
		lm2->set_definition_x("1");
		lm2->set_definition_y("1");

		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("lm3");
		lm3->set_definition_x("0");
		lm3->set_definition_y("0");

		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("lm4");
		lm4->set_definition_x("1");
		lm4->set_definition_y("1");

		list<ustring> landmark_names;
		landmark_names.push_back("lm1");
		landmark_names.push_back("lm2");
		landmark_names.push_back("lm3");
		landmark_names.push_back("lm4");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<CurveDefinition> bezier = shared_ptr<CurveDefinition>(new BezierDefinition);
		bezier->set_name("bezier1");
		bezier->set_landmarks(landmark_names);
		shared_ptr<CurveEvaluationTreeNode> bezier_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));

		lm2->set_definition_x(".5");
		lm2->set_definition_y(".5");

		lm4->set_definition_x(".5");
		lm4->set_definition_y(".5");

		BezierComplex evaluated_bezier = bezier_node->get_value();

		CHECK_CLOSE(.0, evaluated_bezier.get_coordinate(.0).get_x(), 1e-6);
		CHECK_CLOSE(.0, evaluated_bezier.get_coordinate(.0).get_y(), 1e-6);
		CHECK_CLOSE(.25, evaluated_bezier.get_coordinate(.5).get_x(), 1e-6);
		CHECK_CLOSE(.25, evaluated_bezier.get_coordinate(.5).get_y(), 1e-6);
		CHECK_CLOSE(.50, evaluated_bezier.get_coordinate(1.0).get_x(), 1e-6);
		CHECK_CLOSE(.50, evaluated_bezier.get_coordinate(1.0).get_y(), 1e-6);
	}

	TEST(SetCurveLandmarkToNonexistingLandmark)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("lm1");
		lm1->set_definition_x("0");
		lm1->set_definition_y("0");

		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("lm2");
		lm2->set_definition_x("1");
		lm2->set_definition_y("1");

		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("lm3");
		lm3->set_definition_x("0");
		lm3->set_definition_y("0");

		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("lm4");
		lm4->set_definition_x("1");
		lm4->set_definition_y("1");

		list<ustring> landmark_names;
		landmark_names.push_back("lm1");
		landmark_names.push_back("lm2");
		landmark_names.push_back("lm3");
		landmark_names.push_back("lm4");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<CurveDefinition> bezier = shared_ptr<CurveDefinition>(new BezierDefinition);
		bezier->set_name("bezier1");
		bezier->set_landmarks(landmark_names);
		shared_ptr<CurveEvaluationTreeNode> bezier_node
            = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));

        landmark_names.pop_back();
        landmark_names.push_back("fooBar");
        CHECK_THROW(bezier->set_landmarks(landmark_names),
            MyPattern::Exceptions::UnmetDependenciesEvaluationException);
	}

	TEST(CalculateLandmarkRelativeToCurve)
	{
		EvaluationRoot root = EvaluationRoot();

		shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
		lm1->set_name("lm1");
		lm1->set_definition_x("0");
		lm1->set_definition_y("0");

		shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
		lm2->set_name("lm2");
		lm2->set_definition_x(".5");
		lm2->set_definition_y(".5");

		shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
		lm3->set_name("lm3");
		lm3->set_definition_x(".5");
		lm3->set_definition_y(".5");

		shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
		lm4->set_name("lm4");
		lm4->set_definition_x("1");
		lm4->set_definition_y("1");

		shared_ptr<Landmark> lm_check = shared_ptr<Landmark>(new Landmark());
		lm_check->set_name("lm_check");
		lm_check->set_definition_x("$bezier1[.5][X]");
		lm_check->set_definition_y("$bezier1[.5][Y]");

		list<ustring> landmark_names;
		landmark_names.push_back("lm1");
		landmark_names.push_back("lm2");
		landmark_names.push_back("lm3");
		landmark_names.push_back("lm4");

		root.add_object(lm1);
		root.add_object(lm2);
		root.add_object(lm3);
		root.add_object(lm4);

		shared_ptr<CurveDefinition> bezier = shared_ptr<CurveDefinition>(new BezierDefinition);
		bezier->set_name("bezier1");
		bezier->set_landmarks(landmark_names);
		shared_ptr<CurveEvaluationTreeNode> bezier_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(root.add_object(bezier));
		shared_ptr<LandmarkEvaluationTreeNode> lm_check_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(lm_check));

        Point lm_check_node_value = lm_check_node->get_value();

        CHECK_CLOSE(.5, lm_check_node_value.get_x(), 1e-6);
        CHECK_CLOSE(.5, lm_check_node_value.get_y(), 1e-6);
	}

	TEST(AddMeasureValue)
	{
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<MeasureValue> measureValue = shared_ptr<MeasureValue>(new MeasureValue("test", "Dummy", 1.234));

        shared_ptr<MeasureValueEvaluationTreeNode> added_node = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(root.add_object(measureValue));

        CHECK_EQUAL(true, added_node != NULL);
	}

	TEST(GetAddedMeasureValuePrefixedName)
	{
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<MeasureValue> measureValue = shared_ptr<MeasureValue>(new MeasureValue("test", "Ein einfacher Testwert", 6.485));
        shared_ptr<MeasureValueEvaluationTreeNode> added_node = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(root.add_object(measureValue));

        CHECK_EQUAL("#test", added_node->get_prefixed_name());
	}

	TEST(GetAddedMeasureValueDefaultValue)
	{
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<MeasureValue> measureValue = shared_ptr<MeasureValue>(new MeasureValue("test", "Blah blah blah", 3.14159));
        shared_ptr<MeasureValueEvaluationTreeNode> added_node = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(root.add_object(measureValue));

        CHECK_EQUAL(3.14159, added_node->get_value());
	}

	TEST(GetAddedMeasureValueSetName)
	{
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<MeasureValue> measureValue = shared_ptr<MeasureValue>(new MeasureValue("bla", "", 3.14159));
        shared_ptr<MeasureValueEvaluationTreeNode> added_node = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(root.add_object(measureValue));

        measureValue->set_value(1.2345);
        CHECK_EQUAL(1.2345, added_node->get_value());
	}

    TEST(AddLandmarkWithReferenceToMeasureValue)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<MeasureValue> measureValue = shared_ptr<MeasureValue>(new MeasureValue("mv", "", 2.718281828));
        shared_ptr<MeasureValueEvaluationTreeNode> n_measureValue = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(root.add_object(measureValue));

        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("lm");
        landmark->set_definition_x("#mv");
        landmark->set_definition_y("0");

        shared_ptr<LandmarkEvaluationTreeNode> n_landmark = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(landmark));
        Point p = n_landmark->get_value();

        CHECK_EQUAL(2.718281828, p.get_x());
        CHECK_EQUAL(0, p.get_y());
    }

    TEST(MeasureValueNotifyDependentValues)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<MeasureValue> measureValue = shared_ptr<MeasureValue>(new MeasureValue("mv", "", 20.0188));
        shared_ptr<MeasureValueEvaluationTreeNode> n_measureValue = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(root.add_object(measureValue));

        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("lm");
        landmark->set_definition_x("#mv");
        landmark->set_definition_y("0");

        shared_ptr<LandmarkEvaluationTreeNode> n_landmark = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(root.add_object(landmark));

        measureValue->set_value(6.0485);

        Point p = n_landmark->get_value();

        CHECK_EQUAL(6.0485, p.get_x());
        CHECK_EQUAL(0, p.get_y());
    }
}
