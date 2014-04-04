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

BezierComplex CurveEvaluationTreeNode::get_value()
{
	std::list<Point> points;



	return m_base_curve_definition->get_bezier(points);
	
	//return BezierComplex(list<Bezier>(), "");
}

void CurveEvaluationTreeNode::base_curve_changed()
{
	if(!signal_update_dependencies.empty())
	{
		signal_update_dependencies(shared_from_this());
	}
}

bool CurveEvaluationTreeNode::base_curve_change_request(list<ustring> new_landmarks)
{
	if(!signal_request_change.empty())
	{
		return signal_request_change(shared_from_this(),new_landmarks);
	}
	return true;
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
