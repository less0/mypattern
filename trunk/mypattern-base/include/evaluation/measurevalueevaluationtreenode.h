#ifndef MYPATTERN_EVALUATION_MEASUREVALUEEVALUATIONTREENODE_H
#define MYPATTERN_EVALUATION_MEASUREVALUEEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>
#include <measurevalue.h>
#include <glibmm/ustring.h>
#include <list>

using namespace std;
using namespace MyPattern::Base;

namespace MyPattern {
namespace Base {
namespace Evaluation {

class MeasureValueEvaluationTreeNode : public EvaluationTreeNode
{
    public:
        MeasureValueEvaluationTreeNode(shared_ptr<MeasureValue>);

        void notify_update() {}
        list<ustring> depends_on()
        {
            return list<Glib::ustring>();
        }
        Glib::ustring get_prefixed_name();
        double get_value();

        sigc::signal1<void, shared_ptr<MeasureValueEvaluationTreeNode>> signal_changed;
    protected:
        void update_value()
        {
            if(!m_signal_update.empty())
            {
                m_signal_update();
            }
        }
    private:
        void base_measure_value_changed()
        {
            update_value();
        }

        shared_ptr<MeasureValue> m_base_measurevalue;

};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_EVALUATION_MEASUREVALUEEVALUATIONTREENODE_H
