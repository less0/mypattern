#ifndef EVALUATIONTREENODE_H
#define EVALUATIONTREENODE_H

/** \brief Node of the evaluation tree
*
* For reasons of efficiency, all objects to be evaluated are organized in a tree
* and whenever an object changes, it notifies an observer (i.e. the
* EvaluationTreeNode) about the changes. The node in turn notifies the
*/
class EvaluationTreeNode
{
    public:
        EvaluationTreeNode();
        virtual ~EvaluationTreeNode();
    protected:
    private:
};

#endif // EVALUATIONTREENODE_H
