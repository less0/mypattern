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

std::list<Glib::ustring> CurveEvaluationTreeNode::depends_on()
{
    std::list<Glib::ustring> landmark_names = m_base_curve_definition->get_landmarks();
    std::list<Glib::ustring> dependencies;

    for(std::list<Glib::ustring>::iterator it = landmark_names.begin(); it != landmark_names.end(); it++)
    {
        dependencies.push_back("@" + *it);
    }

    return dependencies;
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern