#ifndef EVALUATIONTREENODE_H
#define EVALUATIONTREENODE_H

#include "evaluation/evaluationtreeobserver.h"
#include <memory>
#include <list>
#include <map>
#include <string>
#include "sigc++/sigc++.h"

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
class EvaluationTreeNode : public std::enable_shared_from_this<EvaluationTreeNode>
{
    public:
        sigc::signal<void> signal_update()
        {
            return m_signal_update;
        }

        void add_dependency(shared_ptr<EvaluationTreeNode>);
        void remove_dependency(shared_ptr<EvaluationTreeNode>);
        void clear_dependencies();
        list<shared_ptr<EvaluationTreeNode>> get_nodes();

        bool depends_on(string);

        virtual void notify_update() = 0;

        virtual list<string> depends_on() = 0;

        virtual string get_prefixed_name() = 0;

    protected:
        list<shared_ptr<EvaluationTreeNode>> m_nodes;
        std::map<long,sigc::connection> m_signal_connections;

        sigc::signal<void> m_signal_update;

        /*! \brief Updates the value of the node's object
         */
        virtual void update_value() = 0;
    private:

};
}
}
}


#endif // EVALUATIONTREENODE_H
