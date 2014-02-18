#ifndef MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H
#define MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>

namespace MyPattern {
namespace Base {
namespace Evaluation {

class LandmarkEvaluationTreeNode : public MyPattern::Base::Evaluation::EvaluationTreeNode
{
    public:
        /** Default constructor */
        LandmarkEvaluationTreeNode();
        ~LandmarkEvaluationTreeNode()
        {}

        void notify_update() {}

        list<ustring> depends_on() {}
    protected:
    private:
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H
