#include "curvedefinition.h"

using namespace MyPattern::Base;


list<shared_ptr<CurveDefinition>> CurveDefinition::m_registered_classes = list<shared_ptr<CurveDefinition>>();

CurveDefinition::~CurveDefinition()
{}

Glib::ustring CurveDefinition::get_name()
{
    return m_name;
}

bool CurveDefinition::set_name(Glib::ustring name)
{
    if(request_name_change.empty() || request_name_change(name, OBJECTTYPE_CURVE))
    {
        Glib::ustring old_name = m_name;

        m_name = name;

        if(!signal_name_changed.empty())
        {
            this->signal_name_changed.emit();
        }

        return true;
    }
    else
    {
        return false;
    }

}

list<ustring> CurveDefinition::get_landmarks()
{
    return m_landmarks;
}

void CurveDefinition::set_landmarks(list<ustring> landmarks)
{
    if(signal_request_change.empty() || signal_request_change(landmarks))
    {
        m_landmarks = landmarks;

        if(!signal_changed.empty())
        {
            signal_changed();
        }
    }
}

void CurveDefinition::register_class(shared_ptr<CurveDefinition> prototype)
{
    for(list<shared_ptr<CurveDefinition>>::iterator it = m_registered_classes.begin();
        it != m_registered_classes.end();
        it++)
    {
        if((*it)->get_class_name() == prototype->get_class_name());
        {
            //TODO (paul#8#) throw exception class object
            throw "";
        }
    }

    CurveDefinition::m_registered_classes.push_back(prototype);
}

list<ustring> CurveDefinition::get_registered_class_names()
{
    list<ustring> names;

    for(list<shared_ptr<CurveDefinition>>::iterator it = CurveDefinition::m_registered_classes.begin();
        it != CurveDefinition::m_registered_classes.end();
        it++)
    {
        names.push_back((*it)->get_class_name());
    }

    return names;
}


shared_ptr<CurveDefinition> CurveDefinition::deserialize(XmlNode node)
{
    if(node.get_name() != "curve")
    {
        throw MyPattern::Exceptions::Exception();
    }

    shared_ptr<CurveDefinition> deserialized_definition = shared_ptr<CurveDefinition>(NULL);
    list<XmlAttribute> attributes;
    ustring type;

    attributes = node.get_attributes();

    for(list<XmlAttribute>::iterator it = attributes.begin();
        it != attributes.end();
        it++)
    {
        if(it->get_name() == "type")
        {
            type = it->get_value();
        }
    }

    for(list<shared_ptr<CurveDefinition>>::iterator it = m_registered_classes.begin();
        it != m_registered_classes.end();
        it++)
    {
        if((*it)->get_class_name() == type)
        {
            (*it)->deserialize_from_xml(node);
        }
    }

    return deserialized_definition;
}

//shared_ptr<CurveDefinition> CurveDefinition::deserialize_from_xml(XmlNode)
//{
//    return nullptr;
//}

