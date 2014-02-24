#ifndef MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H
#define MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>
#include <landmark.h>

namespace MyPattern {
namespace Base {
namespace Evaluation {

class LandmarkEvaluationTreeNode : public MyPattern::Base::Evaluation::EvaluationTreeNode
{
    public:
        /** Default constructor */
        LandmarkEvaluationTreeNode();

        LandmarkEvaluationTreeNode(shared_ptr<Landmark> landmark)
        {
            m_base_landmark = landmark;
        }

        ~LandmarkEvaluationTreeNode()
        {}

        void notify_update() {}

        list<ustring> depends_on() { return m_base_landmark->depends_on(); }

        shared_ptr<Landmark> get_landmark()
        {
            return m_base_landmark;
        }

        ustring get_prefixed_name();
    protected:
    private:
        shared_ptr<Landmark> m_base_landmark;
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H
