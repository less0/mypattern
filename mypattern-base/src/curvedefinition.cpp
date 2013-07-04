#include "curvedefinition.h"

CurveDefinition::~CurveDefinition()
{
    //dtor
}

Glib::ustring CurveDefinition::get_name()
{
    return m_name;
}

bool CurveDefinition::set_name(Glib::ustring name)
{
    if(request_name_change.emit(name, PARTTYPE_CURVE))
    {
        m_name = name;
        return true;
    }
    else
    {
        return false;
    }

}

list<ustring> CurveDefinition::get_landmark_names()
{
    list<ustring> landmark_names(0);
    list<shared_ptr<Landmark>>::iterator it = m_landmarks.begin();

    while(it != m_landmarks.end())
    {
        landmark_names.push_back((*it)->get_name());
        it++;
    }

    return landmark_names;
}

bool CurveDefinition::add_landmark(shared_ptr<Landmark> landmark)
{
    if(int(this->m_landmarks.size()) < this->get_max_landmarks())
    {
        this->m_landmarks.push_back(landmark);
        return true;
    }
    else
    {
        return false;
    }
}

