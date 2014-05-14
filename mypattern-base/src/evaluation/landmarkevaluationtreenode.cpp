#include "evaluation/landmarkevaluationtreenode.h"
#include "evaluation/curveevaluationtreenode.h"
#include "evaluation/measurevalueevaluationtreenode.h"
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
		//first separate the symbol name and the symbol parameters
		ustring current_symbol = *it_symbols;
		ustring current_symbol_base = "";
		list<ustring> parameters;
		bool has_parameters = false;

		ustring::size_type index_of_bracket = 0;

        //!\todo replace with while loop and find
		while((index_of_bracket = current_symbol.find('[', index_of_bracket + 1)) != ustring::npos)
		{
			ustring::size_type index_of_closing_bracket;
			has_parameters = true;

			if((index_of_closing_bracket = current_symbol.find(']', index_of_bracket)) != ustring::npos)
			{
                if(current_symbol_base == "")
                {
                    current_symbol_base = current_symbol.substr(0, index_of_bracket);
                }
				parameters.push_back(current_symbol.substr(index_of_bracket + 1, index_of_closing_bracket - index_of_bracket - 1));
			}
			else
			{
				std::cerr << "Did not find closing bracket of parameter" << std::endl;
				throw MyPattern::Exceptions::EvaluationException();
			}
		}

		if(!has_parameters)
		{
			current_symbol_base = current_symbol;
		}

		// iterate over all nodes
		for(list<shared_ptr<EvaluationTreeNode>>::iterator it_nodes = m_nodes.begin(); it_nodes != m_nodes.end(); it_nodes++)
		{
			if((*it_nodes)->get_prefixed_name() == current_symbol_base)
			{
				if(current_symbol_base[0] == '@') //the current child node is a landmark
				{
					shared_ptr<LandmarkEvaluationTreeNode> child_landmark = dynamic_pointer_cast<LandmarkEvaluationTreeNode>(*it_nodes);

					if(child_landmark != NULL)
					{
						if(!has_parameters || parameters.size() != 1)
						{
							throw MyPattern::Exceptions::EvaluationException();
						}

						Glib::ustring parameter = parameters.front();

						if(parameter == "X" || parameter == "x")
						{
							values.insert(std::pair<ustring,double>(current_symbol, child_landmark->get_value().get_x()));
						}
						else if(parameter == "Y" || parameter == "y")
						{
							values.insert(std::pair<ustring,double>(current_symbol, child_landmark->get_value().get_y()));
						}
						else
						{
							std::cerr << "Invalid point argument: " << parameter << " Current symbol: " << current_symbol << std::endl;
							throw MyPattern::Exceptions::EvaluationException();
						}
					}
					else
					{
						std::cerr << "Could not cast EvaluationTreeNode to LandmarkEvaluationTreeNode." << std::endl;
						throw MyPattern::Exceptions::EvaluationException();
					}
				}
				else if(current_symbol_base[0] == '$') //the current child node is a curve
				{
                    shared_ptr<CurveEvaluationTreeNode> child_curve = dynamic_pointer_cast<CurveEvaluationTreeNode>(*it_nodes);

                    if(child_curve != NULL)
                    {
                        if(!has_parameters || parameters.size() != 2)
                        {
                            throw MyPattern::Exceptions::EvaluationException();
                        }

                        Glib::ustring parameter_1;
                        Glib::ustring parameter_2;
                        double fractionOfCurve = -1.0;
                        Glib::ustring coordinate = "";
                        Point positionAtCurve;
                        list<ustring>::iterator it_parameters= parameters.begin();
                        BezierComplex evaluatedCurve;

                        parameter_1 = *it_parameters++;
                        parameter_2 = *it_parameters;

                        coordinate = parameter_2;

                        stringstream sstream(parameter_1);
                        sstream >> fractionOfCurve;

                        if(fractionOfCurve < .0 || fractionOfCurve > 1.0)
                        {
                            throw MyPattern::Exceptions::EvaluationException();
                        }

                        evaluatedCurve = child_curve->get_value();
                        positionAtCurve = evaluatedCurve.get_coordinate(fractionOfCurve);

                        if(coordinate == "X" || coordinate == "x")
                        {
                            values.insert(std::pair<Glib::ustring, double>(current_symbol, positionAtCurve.get_x()));
                        }
                        else if(coordinate == "Y" || coordinate == "y")
                        {
                            values.insert(std::pair<Glib::ustring, double>(current_symbol, positionAtCurve.get_y()));
                        }
                        else
                        {
                            throw MyPattern::Exceptions::EvaluationException();
                        }
                    }
                    else
                    {
                        throw MyPattern::Exceptions::EvaluationException();
                    }
				}
				else if(current_symbol[0] == '#')
				{
                    shared_ptr<MeasureValueEvaluationTreeNode> child_measure = dynamic_pointer_cast<MeasureValueEvaluationTreeNode>(*it_nodes);

                    if(child_measure != NULL)
                    {
                        values.insert(std::pair<Glib::ustring,double>(current_symbol_base, child_measure->get_value()));
                    }
                    else
                    {
                        throw MyPattern::Exceptions::EvaluationException();
                    }
				}
			}
		}
	}

	m_cached_value = m_base_landmark->get_point(values);

	if(!m_signal_update.empty())
	{
		m_signal_update();
	}
}

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern
