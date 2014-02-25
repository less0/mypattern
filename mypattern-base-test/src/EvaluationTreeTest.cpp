#include "UnitTest++.h"
#include "mypattern-base.h"

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

        CHECK_THROW(root.add_object(landmark1), MyPattern::Exceptions::CircularDependencyEvaluationException);
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

    TEST(CheckLandmarkObservers)
    {
        EvaluationRoot root = EvaluationRoot();

        shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
        shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());

        lm1->set_name("lm1");

        lm2->set_name("lm2");
        lm2->set_definition_y("@lm1[X]");

        shared_ptr<EvaluationTreeNode> lm1_node = root.add_object(lm1);
        shared_ptr<EvaluationTreeNode> lm2_node = root.add_object(lm2);
        list<shared_ptr<EvaluationTreeObserver>> lm2_observers = lm2_node->get_observers();

        CHECK_EQUAL(1, lm2_observers.size());

        list<shared_ptr<EvaluationTreeObserver>>::iterator it = lm2_observers.begin();

        CHECK_EQUAL(*it, lm1_node);
    }

    TEST(ChangeLandmarkDefinition)
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
}
