#include "UnitTest++.h"
#include "evaluation/evaluationroot.h"
#include "patternobject.h"
#include "landmark.h"

using namespace MyPattern::Base;
using namespace MyPattern::Base::Evaluation;

namespace
{
    TEST(AddLandmarkToTree)
    {
        EvaluationRoot root = EvaluationRoot();
        shared_ptr<PatternObject> landmark = shared_ptr<PatternObject>(new Landmark());


        shared_ptr<EvaluationTreeNode> node =  root.add_object(landmark);
        CHECK_EQUAL(true, node != NULL);
    }
}
