#include "evaluation/evaluationroot.h"
#include "landmark.h"
#include "evaluation/landmarkevaluationtreenode.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {

    EvaluationRoot::EvaluationRoot()
    {

    }

    shared_ptr<EvaluationTreeNode> EvaluationRoot::add_object(shared_ptr<PatternObject> object)
    {



        shared_ptr<Landmark> p_landmark = dynamic_pointer_cast<Landmark>(object);


        if(p_landmark != NULL)
        {
            return shared_ptr<EvaluationTreeNode>(new LandmarkEvaluationTreeNode());
        }

        return shared_ptr<EvaluationTreeNode>(NULL);
    }

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
