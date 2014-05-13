#include "curvedefinition.h"

using namespace MyPattern::Base;

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

//bool CurveDefinition::add_landmark(shared_ptr<Landmark> landmark)
//{
//    if(int(this->m_landmarks.size()) < this->get_max_landmarks())
//    {
//        this->m_landmarks.push_back(landmark);
//
//        if(!this->signal_changed.empty())
//            this->signal_changed.emit();
//
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//bool CurveDefinition::add_landmark(shared_ptr<Landmark> landmark, ustring after)
//{
//    list<shared_ptr<Landmark>>::iterator it = m_landmarks.begin();
//
//    if(int(this->m_landmarks.size()) < this->get_max_landmarks())
//    {
//        while(it != m_landmarks.end())
//        {
//            if((*it)->get_name() == after)
//            {
//                m_landmarks.insert(++it, landmark);
//
//                this->signal_changed();
//
//                return true;
//            }
//        }
//        return false;
//    }
//    return false;
//}
//
//
//bool CurveDefinition::remove_landmark(Glib::ustring name)
//{
//    list<shared_ptr<Landmark>>::iterator it = m_landmarks.begin();
//
//    while(it != m_landmarks.end())
//    {
//        if((*it)->get_name() == name)
//        {
//            m_landmarks.erase(it);
//
//            return true;
//        }
//
//        it++;
//    }
//
//    return false;
//}
