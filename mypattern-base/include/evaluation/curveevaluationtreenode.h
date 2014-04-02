#ifndef MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H
#define MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>
#include <curvedefinition.h>

namespace MyPattern {
namespace Base {
namespace Evaluation {

class CurveEvaluationTreeNode : public MyPattern::Base::Evaluation::EvaluationTreeNode
{
    public:
        /** Default constructor */
        CurveEvaluationTreeNode(shared_ptr<CurveDefinition>);

        void notify_update(){}

        list<ustring> depends_on();

        ustring get_prefixed_name();

	/*! \brief Gets the last evaluated value of the associated CurveDefinition
	 * given the values of the dependencies
	 */
	BezierComplex get_value();
    protected:
        void update_value() {}
    private:
        shared_ptr<CurveDefinition> m_base_curve_definition;

	
        /*! \brief Signal handler for Landmark::signal_request_change */
        bool base_curve_change_request(list<ustring> new_dependencies);

        /*! \brief Signal handler for Landmark::signal_change */
        void base_curve_changed();
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H
