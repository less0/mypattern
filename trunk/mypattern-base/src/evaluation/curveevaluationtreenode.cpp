#include "evaluation/curveevaluationtreenode.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {

CurveEvaluationTreeNode::CurveEvaluationTreeNode(shared_ptr<CurveDefinition> base_curve_definition)
{
    m_base_curve_definition = base_curve_definition;
}

Glib::ustring CurveEvaluationTreeNode::get_prefixed_name()
{
    return "$" + m_base_curve_definition->get_name();
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
