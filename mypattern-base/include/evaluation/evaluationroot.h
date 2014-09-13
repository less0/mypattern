#ifndef MYPATTERN_BASE_EVALUATION_EVALUATIONROOT_H
#define MYPATTERN_BASE_EVALUATION_EVALUATIONROOT_H

#include "evaluation/evaluationtreenode.h"
#include "point.h"
#include "beziercomplex.h"
#include "patternobject.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {

class EvaluationRoot
{
    public:
        /*! \brief Default constructor */
        EvaluationRoot();

        list<Point> get_points();
        list<BezierComplex> get_curves();

        /*! \brief Adds a node to the evaluation tree.
         *
         * If the node is in the tree afterwards the functions runs successful,
         * but returns false if the object has already been in the list. If the
         * node could not be added for any reason, an exception of the type
         * EvaluationTreeException (which is derived of EvaluationException) is
         * thrown
         *
         * \return true if the node has not been in the tree before false if it
         * has been.
         */
        bool add_node(shared_ptr<EvaluationTreeNode>);
        bool remove_node(shared_ptr<EvaluationTreeNode>);

        shared_ptr<EvaluationTreeNode> add_object(const shared_ptr<PatternObject>&);
        list<shared_ptr<EvaluationTreeNode>> add_objects(list<shared_ptr<PatternObject>>);
        list<shared_ptr<EvaluationTreeNode>> resolve_dependencies(list<ustring> dependency_names);
    protected:
    private:
        list<shared_ptr<EvaluationTreeNode>> m_tree_nodes;

        bool landmark_node_change_request(shared_ptr<EvaluationTreeNode>,list<ustring>);
        void landmark_update_dependencies(shared_ptr<EvaluationTreeNode>);

        bool curve_node_change_request(shared_ptr<EvaluationTreeNode>, list<ustring>);
        void curve_update_dependencies(shared_ptr<EvaluationTreeNode>);
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_EVALUATIONROOT_H
