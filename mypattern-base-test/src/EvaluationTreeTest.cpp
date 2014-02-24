#include "UnitTest++.h"
#include "evaluation/evaluationroot.h"
#include "evaluation/landmarkevaluationtreenode.h"
#include "patternobject.h"
#include "landmark.h"
#include "exceptions/objectnametakenevaluationexception.h"
#include "exceptions/unmetdependenciesevaluationexception.h"

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
}
