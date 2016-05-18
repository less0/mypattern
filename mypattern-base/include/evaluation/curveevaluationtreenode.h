#ifndef MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H
#define MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>
#include <curvedefinition.h>
#include <string>

using namespace std;

namespace MyPattern {
namespace Base {
namespace Evaluation {

class CurveEvaluationTreeNode : public MyPattern::Base::Evaluation::EvaluationTreeNode
{
    public:
        /** Default constructor */
        CurveEvaluationTreeNode(shared_ptr<CurveDefinition>);

        void notify_update();

        list<string> depends_on();

        string get_prefixed_name();

        /*! \brief Gets the last evaluated value of the associated CurveDefinition
         * given the values of the dependencies
         */
        BezierComplex get_value();

        /*! \brief Gets the signal that checks the validity of a dependency
         * change */
        sigc::signal2<bool, shared_ptr<EvaluationTreeNode>, list<string>> signal_request_change;

        /*! \brief Returns the signal that is emitted when the object has been
         * updated and the dependencies are to be updated by the EvaluationRoot */
        sigc::signal1<void, shared_ptr<EvaluationTreeNode>> signal_update_dependencies;
    protected:
        void update_value();
    private:
        shared_ptr<CurveDefinition> m_base_curve_definition;
	BezierComplex m_last_value;

	void base_curve_changed();
	bool base_curve_change_request(list<string>);
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H
