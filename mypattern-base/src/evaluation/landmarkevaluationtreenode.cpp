#include "evaluation/landmarkevaluationtreenode.h"
#include <exceptions/evaluationexception.h>
#include <iostream>
#include <map>

namespace MyPattern {
namespace Base {
namespace Evaluation {

LandmarkEvaluationTreeNode::LandmarkEvaluationTreeNode()
{
    //ctor
}

LandmarkEvaluationTreeNode::LandmarkEvaluationTreeNode(shared_ptr<Landmark> landmark)
{
    m_base_landmark = landmark;

    m_base_landmark->signal_change_request.connect(sigc::mem_fun(this, &LandmarkEvaluationTreeNode::base_landmark_change_request));
    m_base_landmark->signal_changed.connect(sigc::mem_fun(this, &LandmarkEvaluationTreeNode::base_landmark_changed));
}

ustring LandmarkEvaluationTreeNode::get_prefixed_name()
{
    return "@" + m_base_landmark->get_name();
}

bool LandmarkEvaluationTreeNode::base_landmark_change_request(list<ustring> new_dependencies)
{
    sigc::signal2<bool, shared_ptr<EvaluationTreeNode>, list<ustring>>::slot_list_type slots = signal_request_change.slots();

    if(slots.begin() != slots.end())
    {
        return signal_request_change(shared_from_this(), new_dependencies);
    }

    return true;
}

void LandmarkEvaluationTreeNode::base_landmark_changed()
{
    sigc::signal1<void, shared_ptr<EvaluationTreeNode>>::slot_list_type slots = signal_update_dependencies.slots();

    if(slots.begin() != slots.end())
    {
        signal_update_dependencies(shared_from_this());
    }

    update_value();
}

Point LandmarkEvaluationTreeNode::get_value()
{
	return m_cached_value;
}

void LandmarkEvaluationTreeNode::notify_update()
{
	update_value();
}

void LandmarkEvaluationTreeNode::update_value()
{
	list<ustring> formula_symbols = m_base_landmark->depends_on(false);
	std::map<ustring, double> values;
	
	for(list<ustring>::iterator it_symbols = formula_symbols.begin(); it_symbols != formula_symbols.end(); it_symbols++)
	{
		//first separate the symbol name and the symbol parameter

		ustring current_symbol = *it_symbols;
		ustring current_symbol_base;
		ustring parameter;
		bool has_parameter;		

		ustring::size_type index_of_bracket = 0;

		if((index_of_bracket = current_symbol.find('[')) != ustring::npos)
		{
			ustring::size_type index_of_closing_bracket;
			has_parameter = true;
			
			if((index_of_closing_bracket = current_symbol.find('[')) != ustring::npos)
			{
				current_symbol_base = current_symbol.substr(0, index_of_bracket);
				parameter = current_symbol.substr(index_of_bracket + 1, index_of_closing_bracket - index_of_bracket - 2);
			}
			else
			{
				std::cerr << "Did not find closing bracket of parameter" << std::endl;
				throw MyPattern::Exceptions::EvaluationException();
			}
		}
		else
		{
			current_symbol_base = current_symbol;
		}

		// iterate over all nodes
		for(list<shared_ptr<EvaluationTreeNode>>::iterator it_nodes = m_nodes.begin(); it_nodes != m_nodes.end(); it_nodes++)
		{
			if((*it_nodes)->get_prefixed_name() == current_symbol_base)
			{
				if(current_symbol_base[0] == '@')
				{
					shared_ptr<LandmarkEvaluationTreeNode> child_landmark = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(*it_nodes);
					
					if(child_landmark != NULL)
					{
						if(!has_parameter)
						{
							throw MyPattern::Exceptions::EvaluationException();
						}
						else if(parameter == "X" || parameter == "x")
						{
							values.insert(std::pair<ustring,double>(current_symbol, child_landmark->get_value().get_x()));
						}
						else if(parameter == "Y" || parameter == "y")
						{
							values.insert(std::pair<ustring,double>(current_symbol, child_landmark->get_value().get_y()));
						}
						else
						{
							std::cerr << "Invalid point argument" << std::endl;
							throw MyPattern::Exceptions::EvaluationException();
						}
					}
					else
					{
						std::cerr << "Could not cast EvaluationTreeNode to LandmarkEvaluationTreeNode." << std::endl;
						throw MyPattern::Exceptions::EvaluationException();
					} 
				}
				
			}	
		}
	}
	
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
