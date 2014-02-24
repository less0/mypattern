#include "evaluation/landmarkevaluationtreenode.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {

LandmarkEvaluationTreeNode::LandmarkEvaluationTreeNode()
{
    //ctor
}

ustring LandmarkEvaluationTreeNode::get_prefixed_name()
{
    return "@" + m_base_landmark->get_name();
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
