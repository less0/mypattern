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

Part PartDefinition::get_part(Measures measures, list<PatternParameterValue> parameterValues)
{
    list<Point> points;
    list<BezierComplex> curves;

    return Part(this->get_name(), points, curves);
}

//PatternError PartDefinition::evaluate_landmark(Glib::ustring landmark_name,
//                                               shared_ptr<list<PatternObject>> object_stack,
//                                               shared_ptr<list<Point>> points,
//                                               shared_ptr<list<BezierComplex>> curves,
//                                               Measures measures,
//                                               list<PatternParameterValue> parameters)
//{
//    shared_ptr<Landmark> current_landmark = this->get_landmark(landmark_name);
//
//    list<Point>::iterator it = points->begin();
//
//    while(!(it == points->end()))
//    {
//        if(it->get_landmark_name() == current_landmark->get_name())
//        {
//            return PatternError();
//        }
//
//        it++;
//    }
//
//    list<PatternObject>::iterator it_object_stack = object_stack->begin();
//
//    while(!(it_object_stack == object_stack->end()))
//    {
//        if(it_object_stack->get_object_type() == OBJECTTYPE_LANDMARK &&
//           it_object_stack->get_object_name() == current_landmark->get_name())
//           {
//                return PatternError(this->get_name(), current_landmark->get_name(), OBJECTTYPE_LANDMARK, ERR_CIRCULAR_DEPENDENCY);
//           }
//    }
//
//    object_stack->push_back(PatternObject(OBJECTTYPE_CURVE, current_landmark->get_name()));
//
//    evaluate landmarks, the current alandmark is depending on
//
//    evaluate curvedefinitions the current landmark is depending on
//
//    evaluate current landmark
//
//    return PatternError();
//}
//
//PatternError PartDefinition::evaluate_curve(Glib::ustring curve_name, shared_ptr<list<PatternObject>> object_stack, shared_ptr<list<Point>> points, shared_ptr<list<BezierComplex>> curves, Measures measures, list<PatternParameterValue> parameters)
//{
//    shared_ptr<CurveDefinition> current_curve_definition = this->get_curve_definition(curve_name);
//
//    list<BezierComplex>::iterator it = curves->begin();
//
//    while(it != curves->end())
//    {
//        if(it->get_name() == current_curve_definition->get_name())
//        {
//            return PatternError();
//        }
//
//        it++;
//    }
//
//    list<PatternObject>::iterator it_object_stack = object_stack->begin();
//
//    while(it_object_stack != object_stack->end())
//    {
//        if(it_object_stack->get_object_type() == OBJECTTYPE_CURVE &&
//           it_object_stack->get_object_name() == current_curve_definition->get_name())
//        {
//            return PatternError(this->get_name(), current_curve_definition->get_name(), OBJECTTYPE_CURVE, ERR_CIRCULAR_DEPENDENCY);
//        }
//
//        it_object_stack++;
//    }
//
//    object_stack->push_back(PatternObject(PARTTYPE_CURVE, current_curve_definition->get_name()));
//
//    return PatternError(this->get_name(),
//                        current_curve_definition->get_name(),
//                        PARTTYPE_CURVE,
//                        "evaluate_curve is not implemented yet");
//}

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
    int numberOfSlots = 0;

    sigc::signal1<bool,Glib::ustring>::slot_list_type slotList = m_signal_name_change_request.slots();
    sigc::signal1<bool,Glib::ustring>::slot_list_type::iterator it = slotList.begin();

    while(it != slotList.end())
    {
        numberOfSlots++;
        it++;
    }

    if(numberOfSlots == 0 ||
        this->m_signal_name_change_request.emit(name))
    {
        this->m_name = name;

        return true;
    }
    return false;
}

//Glib::ustring PartDefinition::get_xml()
//{
//    stringstream result;
//    result << "<part name=\"" << this->get_name() << "\">" << endl;
//
//    list<shared_ptr<Landmark>>::iterator it_landmarks = this->m_landmarks.begin();
//
//    while(it_landmarks != this->m_landmarks.end())
//    {
//        result << (*it_landmarks)->get_xml();
//
//        it_landmarks++;
//    }
//
//    list<shared_ptr<CurveDefinition>>::iterator it_curves = this->m_curve_definitions.begin();
//
//    while(it_curves != this->m_curve_definitions.end())
//    {
//        result << (*it_curves)->get_xml();
//
//        it_curves++;
//    }
//
//    result << "</part>" << endl;
//
//    return result.str();
//}

//shared_ptr<PartDefinition> PartDefinition::get_from_xml(Glib::ustring xml)
//{
//    shared_ptr<PartDefinition> part_definition(new PartDefinition());
//
//
//
//    return part_definition;
//}

sigc::signal1<bool,Glib::ustring> PartDefinition::signal_name_change_request()
{
    return this->m_signal_name_change_request;
}


