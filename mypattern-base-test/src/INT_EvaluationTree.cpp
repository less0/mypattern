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
		root.add_object(bezier22);
	
	}
}
