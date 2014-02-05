#ifndef EVALUATIONTREENODE_H
#define EVALUATIONTREENODE_H

#include "evaluation/evaluationtreeobserver.h"
#include <memory>
#include <list>

using namespace std;

namespace MyPattern
{
namespace Base
{
namespace Evaluation
{
/** \brief Node of the evaluation tree
*
* For reasons of efficiency, all objects to be evaluated are organized in a tree
* and whenever an object changes, it notifies an observer (i.e. the
* EvaluationTreeNode) about the changes. The node in turn notifies the the subsequent
* objects
*/
class EvaluationTreeNode
{
    public:
        EvaluationTreeNode();
        virtual ~EvaluationTreeNode();

        void add_observer(shared_ptr<EvaluationTreeObserver>);
        void remove_observer(shared_ptr<EvaluationTreeObserver>);
    protected:
        list<shared_ptr<EvaluationTreeObserver>> m_observers;
    private:
};
}
}
}


#endif // EVALUATIONTREENODE_H
