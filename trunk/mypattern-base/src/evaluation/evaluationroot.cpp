#include "evaluation/evaluationroot.h"
#include "landmark.h"
#include "evaluation/landmarkevaluationtreenode.h"
#include "exceptions/objectnametakenevaluationexception.h"
#include "exceptions/unmetdependenciesevaluationexception.h"
#include "exceptions/circulardependencyevaluationexception.h"

#include <iostream>

using namespace MyPattern::Exceptions;

namespace MyPattern {
namespace Base {
namespace Evaluation {

    EvaluationRoot::EvaluationRoot()
    {

    }

    shared_ptr<EvaluationTreeNode> EvaluationRoot::add_object(const shared_ptr<PatternObject> &object)
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
                if((*it)->get_prefixed_name() == newNode->get_prefixed_name() || (*it)->depends_on(newNode->get_prefixed_name()))
                {
                    throw CircularDependencyEvaluationException();
                }
            }

            //add dependencies to list of
            for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
            {
                newNode->add_dependency(*it);
                (*it)->add_observer(newNode);
            }

            newNode->notify_update();

            shared_ptr<LandmarkEvaluationTreeNode> landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(newNode);

            landmark_node->signal_request_change.connect(sigc::mem_fun(this, &EvaluationRoot::landmark_node_change_request));
            landmark_node->signal_update_dependencies.connect(sigc::mem_fun(this, &EvaluationRoot::landmark_update_dependencies));

            m_tree_nodes.push_back(newNode);

            return newNode;
        }

        return shared_ptr<EvaluationTreeNode>(NULL);
    }

    list<shared_ptr<EvaluationTreeNode>> EvaluationRoot::resolve_dependencies(list<ustring> deps)
    {
        list<shared_ptr<EvaluationTreeNode>> result;
        list<ustring> unmet_dependencies;

        list<shared_ptr<EvaluationTreeNode>>::iterator it_objects;


        for(list<ustring>::iterator it_deps = deps.begin(); it_deps != deps.end(); it_deps++)
        {
            bool resolved_current_dependency = false;

            for(it_objects = m_tree_nodes.begin(); it_objects != m_tree_nodes.end(); it_objects++)
            {
                if((*it_objects)->get_prefixed_name() == *it_deps)
                {
                    resolved_current_dependency = true;
                    result.push_back(*it_objects);
                    break;
                }
            }

            if(!resolved_current_dependency)
            {
                unmet_dependencies.push_back(*it_deps);
            }

        }

        if(unmet_dependencies.begin() != unmet_dependencies.end())
        {
            throw MyPattern::Exceptions::UnmetDependenciesEvaluationException(unmet_dependencies);
//            throw UnmetDependenciesEvaluationException(unmet_dependencies);
        }


        return result;
    }


    bool EvaluationRoot::landmark_node_change_request(shared_ptr<EvaluationTreeNode> node, list<ustring> new_dependencies)
    {
        shared_ptr<LandmarkEvaluationTreeNode> landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(node);

        if(landmark_node != NULL)
        {
            list<shared_ptr<EvaluationTreeNode>> dependencies = resolve_dependencies(new_dependencies);

            //check for circular dependencies
            for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
            {
                if((*it)->get_prefixed_name() == landmark_node->get_prefixed_name() || (*it)->depends_on(landmark_node->get_prefixed_name()))
                {
                    throw CircularDependencyEvaluationException();
                }
            }

            return true;
        }
        else
        {
            Exception();
        }
    }

    void EvaluationRoot::landmark_update_dependencies(shared_ptr<EvaluationTreeNode> node)
    {
        shared_ptr<LandmarkEvaluationTreeNode> landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(node);

        if(landmark_node != NULL)
        {
            landmark_node->clear_dependencies();
            list<shared_ptr<EvaluationTreeNode>> dependencies = resolve_dependencies(node->depends_on());

            for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
            {
                landmark_node->add_dependency(*it);
            }

        }
    }

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern