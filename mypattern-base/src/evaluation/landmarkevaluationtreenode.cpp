#include "evaluation/landmarkevaluationtreenode.h"
#include <iostream>

namespace MyPattern {
namespace Base {
namespace Evaluation {

LandmarkEvaluationTreeNode::LandmarkEvaluationTreeNode()
{
    //ctor
}

LandmarkEvaluationTreeNode::LandmarkEvaluationTreeNode(shared_ptr<Landmark> landmark)
{
    m_base_landmark = landmark;

    m_base_landmark->signal_change_request.connect(sigc::mem_fun(this, &LandmarkEvaluationTreeNode::base_landmark_change_request));
    m_base_landmark->signal_changed.connect(sigc::mem_fun(this, &LandmarkEvaluationTreeNode::base_landmark_changed));
}

ustring LandmarkEvaluationTreeNode::get_prefixed_name()
{
    return "@" + m_base_landmark->get_name();
}

bool LandmarkEvaluationTreeNode::base_landmark_change_request(list<ustring> new_dependencies)
{
    sigc::signal2<bool, shared_ptr<EvaluationTreeNode>, list<ustring>>::slot_list_type slots = signal_request_change.slots();

    if(slots.begin() != slots.end())
    {
        return signal_request_change(shared_from_this(), new_dependencies);
    }

    return true;
}

void LandmarkEvaluationTreeNode::base_landmark_changed()
{
    sigc::signal1<void, shared_ptr<EvaluationTreeNode>>::slot_list_type slots = signal_update_dependencies.slots();

    if(slots.begin() != slots.end())
    {
        signal_update_dependencies(shared_from_this());
    }
}

Point LandmarkEvaluationTreeNode::get_value()
{
	return Point(.0, .0);
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
