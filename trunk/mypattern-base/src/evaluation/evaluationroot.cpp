#include "evaluation/evaluationroot.h"
#include "landmark.h"
#include "evaluation/landmarkevaluationtreenode.h"
#include "exceptions/objectnametakenevaluationexception.h"

using namespace MyPattern::Exceptions;

namespace MyPattern {
namespace Base {
namespace Evaluation {

    EvaluationRoot::EvaluationRoot()
    {

    }

    shared_ptr<EvaluationTreeNode> EvaluationRoot::add_object(shared_ptr<PatternObject> object)
    {
        shared_ptr<Landmark> p_landmark = dynamic_pointer_cast<Landmark>(object);

        if(p_landmark != NULL)
        {
            list<shared_ptr<EvaluationTreeNode>>::iterator it_nodes = m_tree_nodes.begin();

            while(it_nodes != m_tree_nodes.end())
            {
                shared_ptr<LandmarkEvaluationTreeNode> landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(*it_nodes);

                if(landmark_node != NULL &&
                    landmark_node->get_landmark()->get_name() == p_landmark->get_name())
                {
                    throw ObjectNameTakenEvaluationException();
                }

                it_nodes++;
            }

            shared_ptr<EvaluationTreeNode> newNode = shared_ptr<EvaluationTreeNode>(new LandmarkEvaluationTreeNode(p_landmark));

            //resolve dependencies
            list<shared_ptr<EvaluationTreeNode>> dependencies = resolve_dependencies(newNode->depends_on());

            //check for circular dependencies
            for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
            {
                //
            }

            //add dependencies to list of
            for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
            {
                newNode->add_dependency(*it);
            }

            m_tree_nodes.push_back(newNode);

            return newNode;
        }

        return shared_ptr<EvaluationTreeNode>(NULL);
    }

    list<shared_ptr<EvaluationTreeNode>> EvaluationRoot::resolve_dependencies(list<ustring> deps)
    {
        list<shared_ptr<EvaluationTreeNode>> result;

        list<shared_ptr<EvaluationTreeNode>>::iterator it_objects;
        for(list<ustring>::iterator it_deps = deps.begin(); it_deps != deps.end(); it_deps++)
        {

        }


        return result;
    }

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
