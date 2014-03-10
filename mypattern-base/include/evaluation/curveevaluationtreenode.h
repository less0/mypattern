#ifndef MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H
#define MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>

namespace MyPattern {
namespace Base {
namespace Evaluation {

class CurveEvaluationTreeNode : public MyPattern::Base::Evaluation::EvaluationTreeNode
{
    public:
        /** Default constructor */
        CurveEvaluationTreeNode();
        /** Default destructor */
        ~CurveEvaluationTreeNode();
    protected:
    private:
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_CURVEEVALUATIONTREENODE_H
