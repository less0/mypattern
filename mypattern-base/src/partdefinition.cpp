#include "partdefinition.h"

#include <sstream>


PartDefinition::PartDefinition()
{
    //ctor
}

PartDefinition::~PartDefinition()
{
    //dtor
}

Part PartDefinition::get_part(Measures measures, list<PatternParameterValue> parameterValues)
{
    list<Point> points;
    list<BezierComplex> curves;

    return Part(this->get_name(), points, curves);
}

PatternError PartDefinition::evaluate_landmark(Glib::ustring landmark_name, shared_ptr<list<PatternObject>> object_stack, shared_ptr<list<Point>> points, shared_ptr<list<BezierComplex>> curves, Measures measures, list<PatternParameterValue> parameters)
{
    shared_ptr<Landmark> current_landmark = this->get_landmark(landmark_name);

    list<Point>::iterator it = points->begin();

    while(!(it == points->end()))
    {
        if(it->get_landmark_name() == current_landmark->get_name())
        {
            return PatternError();
        }

        it++;
    }

    list<PatternObject>::iterator it_object_stack = object_stack->begin();

    while(!(it_object_stack == object_stack->end()))
    {
        if(it_object_stack->get_object_type() == PARTTYPE_LANDMARK &&
           it_object_stack->get_object_name() == current_landmark->get_name())
           {
                return PatternError(this->get_name(), current_landmark->get_name(), PARTTYPE_LANDMARK, ERR_CIRCULAR_DEPENDENCY);
           }
    }

    object_stack->push_back(PatternObject(PARTTYPE_LANDMARK, current_landmark->get_name()));

    //evaluate landmarks, the current alandmark is depending on

    //evaluate curvedefinitions the current landmark is depending on

    //evaluate current landmark

    return PatternError();
}

PatternError PartDefinition::evaluate_curve(Glib::ustring curve_name, shared_ptr<list<PatternObject>> object_stack, shared_ptr<list<Point>> points, shared_ptr<list<BezierComplex>> curves, Measures measures, list<PatternParameterValue> parameters)
{
    shared_ptr<CurveDefinition> current_curve_definition = this->get_curve_definition(curve_name);

    list<BezierComplex>::iterator it = curves->begin();

    while(it != curves->end())
    {
        if(it->get_name() == current_curve_definition->get_name())
        {
            return PatternError();
        }

        it++;
    }

    list<PatternObject>::iterator it_object_stack = object_stack->begin();

    while(it_object_stack != object_stack->end())
    {
        if(it_object_stack->get_object_type() == PARTTYPE_CURVE &&
           it_object_stack->get_object_name() == current_curve_definition->get_name())
        {
            return PatternError(this->get_name(), current_curve_definition->get_name(), PARTTYPE_CURVE, ERR_CIRCULAR_DEPENDENCY);
        }

        it_object_stack++;
    }

    object_stack->push_back(PatternObject(PARTTYPE_CURVE, current_curve_definition->get_name()));

    return PatternError(this->get_name(), current_curve_definition->get_name(), PARTTYPE_CURVE, "evaluate_curve is not implemented yet");
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
    list<shared_ptr<Landmark>>::iterator it = this->m_landmarks.begin();

    while(it != this->m_landmarks.end())
    {
        if((*it)->get_name() == landmark->get_name())
        {
            return false;
        }

        it++;
    }

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
    list<shared_ptr<CurveDefinition>>::iterator it = this->m_curve_definitions.begin();

    while(it != this->m_curve_definitions.end())
    {
        if((*it)->get_name() == curve_definition->get_name())
        {
            return false;
        }

        it++;
    }

    this->m_curve_definitions.push_back(curve_definition);

    return true;
}

Glib::ustring PartDefinition::get_name()
{
    return this->m_name;
}

bool PartDefinition::set_name(Glib::ustring name)
{
    if(this->m_signal_name_change_request.emit(name))
    {
        this->m_name = name;

        return true;
    }
    return false;
}

Glib::ustring PartDefinition::get_xml()
{
    stringstream result;
    result << "<part name=\"" << this->get_name() << "\">" << endl;


    result << "</part>" << endl;

    return result.str();
}
