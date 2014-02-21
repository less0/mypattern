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


            m_tree_nodes.push_back(newNode);

            return newNode;
        }

        return shared_ptr<EvaluationTreeNode>(NULL);
    }

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
