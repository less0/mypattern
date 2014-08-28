#include "partdefinition.h"

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

shared_ptr<Landmark> PartDefinition::get_landmark(Glib::ustring name)
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

shared_ptr<CurveDefinition> PartDefinition::get_curve_definition(Glib::ustring name)
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

Glib::ustring PartDefinition::get_name()
{
    return this->m_name;
}

bool PartDefinition::set_name(Glib::ustring name)
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
	return true;
}

shared_ptr<Measures> PartDefinition::get_measures()
{
	return m_measures;
}

sigc::signal1<bool,Glib::ustring> PartDefinition::signal_name_change_request()
{
    return this->m_signal_name_change_request;
}

