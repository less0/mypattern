#ifndef MYPATTERN_BASE_EVALUATION_EVALUATIONROOT_H
#define MYPATTERN_BASE_EVALUATION_EVALUATIONROOT_H

#include "evaluation/evaluationtreenode.h"
#include "point.h"
#include "beziercomplex.h"
#include "patternobject.h"
#include <string>

using namespace std;

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

        /*! \brief Removes a node from the evaluation tree
         *
         * This method tries to remove a node from the evaluation tree.
         * \return false if the node has not been a node in the current tree,
         * true, if it's been successfully removed.
         * \throw UnmetDependenciesEvaluationException If there are nodes
         * depending on the node to be removed.
         */
        bool remove_node(shared_ptr<EvaluationTreeNode>);

        /*! \brief Tries to create a new EvaluationTreeNode for the
         * PatternObject to be added
         *
         * If the EvaluationTreeNode is created successfully a
         * shared_ptr<EvaluationTreeNode> pointing to this node is returned.
         * If the object exists the respective node will be returned. If the
         * object name is already taken or there are unmet dependencies the
         * respective exceptions are thrown.
         * \throw UnmetDependenciesEvaluationException If the object to be
         * added depends on objects that cannot be resolved
         * \throw ObjectNameTakenEvaluationException If there already is an
         * object with the very name
         * \return Smart pointer to the EvaluationTreeNode for the object
         */
        shared_ptr<EvaluationTreeNode> add_object(const shared_ptr<PatternObject>&);
        list<shared_ptr<EvaluationTreeNode>> add_objects(list<shared_ptr<PatternObject>>);
        list<shared_ptr<EvaluationTreeNode>> resolve_dependencies(list<string> dependency_names);
    protected:
    private:
        list<shared_ptr<EvaluationTreeNode>> m_tree_nodes;

        bool landmark_node_change_request(shared_ptr<EvaluationTreeNode>,list<string>);
        void landmark_update_dependencies(shared_ptr<EvaluationTreeNode>);

        bool curve_node_change_request(shared_ptr<EvaluationTreeNode>, list<string>);
        void curve_update_dependencies(shared_ptr<EvaluationTreeNode>);
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_EVALUATIONROOT_H
