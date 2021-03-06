#include "evaluation/evaluationroot.h"
#include "landmark.h"
#include "curvedefinition.h"
#include "evaluation/landmarkevaluationtreenode.h"
#include "evaluation/curveevaluationtreenode.h"
#include "evaluation/measurevalueevaluationtreenode.h"
#include "exceptions/objectnametakenevaluationexception.h"
#include "exceptions/unmetdependenciesevaluationexception.h"
#include "exceptions/circulardependencyevaluationexception.h"

#include <iostream>

using namespace MyPattern::Exceptions;

namespace MyPattern
{
namespace Base
{
namespace Evaluation
{

EvaluationRoot::EvaluationRoot()
{

}

shared_ptr<EvaluationTreeNode> EvaluationRoot::add_object(const shared_ptr<PatternObject> &object)
{
    shared_ptr<Landmark> p_landmark = dynamic_pointer_cast<Landmark>(object);
    shared_ptr<CurveDefinition> p_curve = dynamic_pointer_cast<CurveDefinition>(object);
    shared_ptr<MeasureValue> p_measurevalue = dynamic_pointer_cast<MeasureValue>(object);

    if(p_landmark != NULL)
    {
        list<shared_ptr<EvaluationTreeNode>>::iterator it_nodes = m_tree_nodes.begin();

        while(it_nodes != m_tree_nodes.end())
        {
            shared_ptr<LandmarkEvaluationTreeNode> landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(*it_nodes);

            if(landmark_node != NULL &&
                    landmark_node->get_landmark()->get_name() == p_landmark->get_name())
            {
                throw ObjectNameTakenEvaluationException(p_landmark->get_name());
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
        }

        newNode->notify_update();

        shared_ptr<LandmarkEvaluationTreeNode> landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(newNode);

        landmark_node->signal_request_change.connect(sigc::mem_fun(this, &EvaluationRoot::landmark_node_change_request));
        landmark_node->signal_update_dependencies.connect(sigc::mem_fun(this, &EvaluationRoot::landmark_update_dependencies));

        m_tree_nodes.push_back(newNode);

        return newNode;
    }
    else if(p_curve != NULL)
    {
        shared_ptr<CurveEvaluationTreeNode> newNode(new CurveEvaluationTreeNode(p_curve));

        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = m_tree_nodes.begin();
                it != m_tree_nodes.end();
                it++)
        {
            shared_ptr<CurveEvaluationTreeNode> existing_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(*it);

            if(existing_node != NULL &&
                    existing_node->get_prefixed_name() == newNode->get_prefixed_name())
            {
                throw ObjectNameTakenEvaluationException(p_curve->get_name());
            }
        }

        list<shared_ptr<EvaluationTreeNode>> dependencies = resolve_dependencies(newNode->depends_on());

        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin();
                it != dependencies.end();
                it++)
        {
            newNode->add_dependency(*it);
        }

        newNode->notify_update();

        newNode->signal_request_change.connect(sigc::mem_fun(this, &EvaluationRoot::curve_node_change_request));
        newNode->signal_update_dependencies.connect(sigc::mem_fun(this, &EvaluationRoot::curve_update_dependencies));

        m_tree_nodes.push_back(newNode);

        return newNode;
    }
    else if(p_measurevalue != NULL)
    {
        shared_ptr<EvaluationTreeNode> newNode =  shared_ptr<EvaluationTreeNode>(new MeasureValueEvaluationTreeNode(p_measurevalue));

        m_tree_nodes.push_back(newNode);

        return newNode;
    }

    return shared_ptr<EvaluationTreeNode>(NULL);
}

list<shared_ptr<EvaluationTreeNode>> EvaluationRoot::add_objects(list<shared_ptr<PatternObject>> objects)
{
    list<shared_ptr<EvaluationTreeNode>> added_nodes;

    bool unresolvable = false;
    list<shared_ptr<PatternObject>> unresolved;

    while(objects.size() > 0 && !unresolvable)
    {
        unresolvable = true;

        for(list<shared_ptr<PatternObject>>::iterator it = objects.begin();
                it != objects.end();
                it++)
        {
            try
            {
                added_nodes.push_back(add_object(*it));
                unresolvable = false;
            }
            catch(UnmetDependenciesEvaluationException e)
            {
                unresolved.push_back(*it);
            }
        }
		
		if(unresolvable)
		{
			throw MyPattern::Exceptions::Exception("There are unresolvable objects");
		}

        objects = unresolved;
        unresolved.clear();
    }


    return added_nodes;
}

list<BezierComplex> EvaluationRoot::get_curves()
{
    list<shared_ptr<EvaluationTreeNode>>::iterator it;
    list<BezierComplex> curves;

    for(it=m_tree_nodes.begin(); it!=m_tree_nodes.end(); it++)
    {
        shared_ptr<CurveEvaluationTreeNode> p_curve_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(*it);

        if(p_curve_node != NULL)
        {
            curves.push_back(p_curve_node->get_value());
        }
    }

    return curves;
}

list<Point> EvaluationRoot::get_points()
{
    list<shared_ptr<EvaluationTreeNode>>::iterator it;
    list<Point> points;

    for(it = m_tree_nodes.begin(); it != m_tree_nodes.end(); it++)
    {
        shared_ptr<LandmarkEvaluationTreeNode> p_landmark_node = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(*it);

        if(p_landmark_node != NULL)
        {
            points.push_back(p_landmark_node->get_value());
        }

    }

    return points;
}

list<shared_ptr<EvaluationTreeNode>> EvaluationRoot::resolve_dependencies(list<string> deps)
{
    list<shared_ptr<EvaluationTreeNode>> result;
    list<string> unmet_dependencies;

    list<shared_ptr<EvaluationTreeNode>>::iterator it_objects;


    for(list<string>::iterator it_deps = deps.begin(); it_deps != deps.end(); it_deps++)
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
    }

    return result;
}


bool EvaluationRoot::landmark_node_change_request(shared_ptr<EvaluationTreeNode> node, list<string> new_dependencies)
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
        throw MyPattern::Exceptions::Exception();
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

bool EvaluationRoot::curve_node_change_request(shared_ptr<EvaluationTreeNode> node, list<string> new_landmarks)
{
    shared_ptr<CurveEvaluationTreeNode> curve_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(node);

    if(curve_node != NULL)
    {
        list<shared_ptr<EvaluationTreeNode>> dependencies = resolve_dependencies(new_landmarks);

        return true;
    }
    else
    {
        throw MyPattern::Exceptions::Exception();
    }
}

void EvaluationRoot::curve_update_dependencies(shared_ptr<EvaluationTreeNode> node)
{
    shared_ptr<CurveEvaluationTreeNode> curve_node = dynamic_pointer_cast<CurveEvaluationTreeNode>(node);

    if(curve_node != NULL)
    {
        curve_node->clear_dependencies();
        list<shared_ptr<EvaluationTreeNode>> dependencies = resolve_dependencies(curve_node->depends_on());

        for(list<shared_ptr<EvaluationTreeNode>>::iterator it = dependencies.begin();
                it != dependencies.end();
                it++)
        {
            curve_node->add_dependency(*it);
        }
    }
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
