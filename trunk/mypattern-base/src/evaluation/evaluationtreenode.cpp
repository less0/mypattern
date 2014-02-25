#include "evaluation/evaluationtreenode.h"
#include "evaluation/evaluationtreeobserver.h"

namespace MyPattern
{
namespace Base
{
namespace Evaluation
{
    void EvaluationTreeNode::add_observer(shared_ptr<EvaluationTreeObserver> observer)
    {
        for(list<shared_ptr<EvaluationTreeObserver>>::iterator it = m_observers.begin(); it != m_observers.end(); it++)
        {
            if(*it == observer)
            {
                return;
            }
        }

        m_observers.push_back(observer);
    }

    void EvaluationTreeNode::remove_observer(shared_ptr<EvaluationTreeObserver> observer)
    {
        for(list<shared_ptr<EvaluationTreeObserver>>::iterator it = m_observers.begin(); it != m_observers.end(); it++)
        {
            if(*it == observer)
            {
                m_observers.remove(*it);

                return;
            }
        }

    }

    void EvaluationTreeNode::add_dependency(shared_ptr<EvaluationTreeNode> treeNode)
    {
        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
        {
            if(*it == treeNode)
            {
                return;
            }
        }

        m_nodes.push_back(treeNode);
    }


    void EvaluationTreeNode::remove_dependency(shared_ptr<EvaluationTreeNode> treeNode)
    {
        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
        {
            if(*it == treeNode)
            {
                m_nodes.remove(*it);

                return;
            }
        }
    }

    bool EvaluationTreeNode::depends_on(ustring name)
    {
        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
        {
            if((*it)->get_prefixed_name() == name || (*it)->depends_on(name))
            {
                return true;
            }
        }

        return false;
    }

    list<shared_ptr<EvaluationTreeNode>> EvaluationTreeNode::get_nodes()
    {
        return m_nodes;
    }

    list<shared_ptr<EvaluationTreeNode>> EvaluationTreeNode::get_observers()
    {
	return m_observers;
    }
}
}
}


