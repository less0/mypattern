#include "evaluation/evaluationtreenode.h"

namespace MyPattern
{
namespace Base
{
namespace Evaluation
{
    void EvaluationTreeNode::add_dependency(shared_ptr<EvaluationTreeNode> treeNode)
    {
        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
        {
            if(*it == treeNode)
            {
                return;
            }
        }

        sigc::connection connection = treeNode->m_signal_update.connect(sigc::mem_fun(this, &EvaluationTreeNode::update_value));

        m_signal_connections.insert(std::pair<long,sigc::connection>(long(&*treeNode), connection));

        m_nodes.push_back(treeNode);
    }


    void EvaluationTreeNode::remove_dependency(shared_ptr<EvaluationTreeNode> treeNode)
    {
        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
        {
            if(*it == treeNode)
            {
                if(m_signal_connections.count(long(&*treeNode)) > 0)
                {
                    m_signal_connections[long(&*treeNode)].disconnect();
                    m_signal_connections.erase(long(&*treeNode));
                }

                m_nodes.remove(*it);

                return;
            }
        }
    }

    void EvaluationTreeNode::clear_dependencies()
    {


        m_signal_connections.clear();
        m_nodes.clear();
    }

    bool EvaluationTreeNode::depends_on(string name)
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


}
}
}


