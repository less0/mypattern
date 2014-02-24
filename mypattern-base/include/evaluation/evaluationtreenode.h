#ifndef EVALUATIONTREENODE_H
#define EVALUATIONTREENODE_H

#include "evaluation/evaluationtreeobserver.h"
#include <memory>
#include <list>
#include "glibmm/ustring.h"

using namespace std;
using namespace Glib;

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
*
* Workflow of changes:
* * object created
* ** get the list of objects it depends on
* ** get the objects EvaluationTreeNode
* ** add the node to EvaluationRoot
* ** EvaluationRoot checks, if the node is valid
* *** get the nodes of objects it depends on
* ** add the nodes to list
* ** re-evaluate
* * object changes
* ** get the list of objects it depends on
* ** "ask" the part if the changes are valid (i.e all dependencies can be resolved,
* no circular dependencies, etc.)
* ** change the formulae
* ** request and save list of nodes it directly depends on
* ** re-evaluate
* ** notify observers about the updated node
*
*/
class EvaluationTreeNode : EvaluationTreeObserver
{
    public:
        void add_observer(shared_ptr<EvaluationTreeObserver>);
        void remove_observer(shared_ptr<EvaluationTreeObserver>);

        void add_dependency(shared_ptr<EvaluationTreeNode>);
        void remove_dependency(shared_ptr<EvaluationTreeNode>);

        virtual void notify_update() = 0;

        virtual list<ustring> depends_on() = 0;
        list<shared_ptr<EvaluationTreeNode>> get_nodes();

        virtual ustring get_prefixed_name() = 0;
    protected:
        list<shared_ptr<EvaluationTreeObserver>> m_observers;
        list<shared_ptr<EvaluationTreeNode>> m_nodes;
    private:

};
}
}
}


#endif // EVALUATIONTREENODE_H
