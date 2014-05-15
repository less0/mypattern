#include "evaluation/measurevalueevaluationtreenode.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {

MeasureValueEvaluationTreeNode::MeasureValueEvaluationTreeNode(shared_ptr<MyPattern::Base::MeasureValue> base_value)
{
    m_base_measurevalue = base_value;
    m_base_measurevalue->signal_changed.connect(sigc::mem_fun(this, &MeasureValueEvaluationTreeNode::base_measure_value_changed));
}

Glib::ustring MeasureValueEvaluationTreeNode::get_prefixed_name()
{
    return "#" + m_base_measurevalue->get_name();
}

double MeasureValueEvaluationTreeNode::get_value()
{
    return m_base_measurevalue->get_value();
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
