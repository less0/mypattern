#include "mypattern-base.h"

#include <sstream>

using namespace MyPattern::Base;


PartDefinition::PartDefinition()
{
    //ctor
}

PartDefinition::~PartDefinition()
{
    //dtor
}

Part PartDefinition::get_part()
{
    list<Point> points = m_evaluationRoot.get_points();
    list<BezierComplex> curves = m_evaluationRoot.get_curves();


    return Part(this->get_name(), points, curves);
}

shared_ptr<Landmark> PartDefinition::get_landmark(string name)
{
    list<shared_ptr<Landmark>>::iterator it = this->m_landmarks.begin();

    while(it != this->m_landmarks.end())
    {
        if((*it)->get_name() == name)
        {
            return *it;
        }

        it++;
    }

    return shared_ptr<Landmark>(NULL);
}

list<shared_ptr<Landmark>> PartDefinition::get_landmarks()
{
    return this->m_landmarks;
}

bool PartDefinition::add_landmark(shared_ptr<Landmark> landmark)
{
    m_evaluationRoot.add_object(landmark);

    this->m_landmarks.push_back(landmark);
    return true;
}

shared_ptr<CurveDefinition> PartDefinition::get_curve_definition(string name)
{
    list<shared_ptr<CurveDefinition>>::iterator it = this->m_curve_definitions.begin();

    while(it != this->m_curve_definitions.end())
    {
        if((*it)->get_name() == name)
        {
            return *it;
        }

        it++;
    }

    return shared_ptr<CurveDefinition>(NULL);
}

list<shared_ptr<CurveDefinition>> PartDefinition::get_curve_definitions()
{
    return this->m_curve_definitions;
}

bool PartDefinition::add_curve_definition(shared_ptr<CurveDefinition> curve_definition)
{
    m_evaluationRoot.add_object(curve_definition);

    this->m_curve_definitions.push_back(curve_definition);  //if the curve was added successfully to evaluation root, add it to the list

    return true;
}

string PartDefinition::get_name()
{
    return this->m_name;
}

bool PartDefinition::set_name(string name)
{
    if(m_signal_name_change_request.empty() ||
        m_signal_name_change_request.emit(name))
    {
        this->m_name = name;

        return true;
    }
    return false;
}

bool PartDefinition::set_measures(shared_ptr<Measures> measures)
{
	m_measures = measures;
    list<shared_ptr<MeasureValue>> measure_values = measures->get_measure_values();

    for(list<shared_ptr<MeasureValue>>::iterator it = measure_values.begin();
        it != measure_values.end();
        it++)
    {
        this->m_evaluationRoot.add_object(*it);
    }

	return true;
}

shared_ptr<Measures> PartDefinition::get_measures()
{
	return m_measures;
}

sigc::signal1<bool,string> PartDefinition::signal_name_change_request()
{
    return this->m_signal_name_change_request;
}

shared_ptr<PartDefinition> PartDefinition::deserialize_from_xml(
                    shared_ptr<XmlNode> node, shared_ptr<Measures> measures)
{
	if(node->get_name() != "part")
	{
		throw ArgumentException("Invalid node");
	}
	
	shared_ptr<PartDefinition> parsedPartDefinition = shared_ptr<PartDefinition>(new PartDefinition());
	parsedPartDefinition->set_measures(measures);
	
	list<XmlAttribute> attributes = node->get_attributes();
	bool parsedName = false;
	
	for(list<XmlAttribute>::iterator it = attributes.begin();
		it != attributes.end();
		it++)
	{
		if(it->get_name() == "name")
		{
			parsedPartDefinition->set_name(it->get_value());
			parsedName = true;
		}
	}
	
	if(!parsedName)
	{
		throw ArgumentException("Name of part missing");
	}
	
	list<shared_ptr<PatternObject>> parsedPatternObjects;
	list<shared_ptr<XmlNode>> subnodes = node->get_nodes();
	
	for(list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();
		it != subnodes.end();
		it++)
	{
		if((*it)->get_name() == "curve")
		{
			shared_ptr<CurveDefinition> parsedCurveDefinition = CurveDefinition::deserialize_from_xml(*it);
			parsedPatternObjects.push_back(parsedCurveDefinition);
			parsedPartDefinition->m_curve_definitions.push_back(parsedCurveDefinition);
		}
		else if((*it)->get_name() == "landmark")
		{
			shared_ptr<Landmark> parsedLandmark = Landmark::deserialize_from_xml(*it);
			parsedPatternObjects.push_back(parsedLandmark);
			parsedPartDefinition->m_landmarks.push_back(parsedLandmark);
		}
		else
		{
			throw ArgumentException("Unknown node type");
		}
	}
	
	parsedPartDefinition->m_evaluationRoot.add_objects(parsedPatternObjects);

	return parsedPartDefinition;
}