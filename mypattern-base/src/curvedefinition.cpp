#include "curvedefinition.h"

using namespace MyPattern::Base;

Glib::ustring CurveDefinition::get_name()
{
    return m_name;
}

bool CurveDefinition::set_name(Glib::ustring name)
{
    if(request_name_change.emit(name, OBJECTTYPE_CURVE))
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

        this->m_signal_changed.emit(shared_ptr<CurveDefinition>(this));

        return true;
    }
    else
    {
        return false;
    }
}

bool CurveDefinition::add_landmark(shared_ptr<Landmark> landmark, ustring after)
{
    list<shared_ptr<Landmark>>::iterator it = m_landmarks.begin();

    if(int(this->m_landmarks.size()) < this->get_max_landmarks())
    {
        while(it != m_landmarks.end())
        {
            if((*it)->get_name() == after)
            {
                m_landmarks.insert(++it, landmark);

                this->m_signal_changed(shared_ptr<CurveDefinition>(this));

                return true;
            }
        }
        return false;
    }
    return false;
}


bool CurveDefinition::remove_landmark(Glib::ustring name)
{
    list<shared_ptr<Landmark>>::iterator it = m_landmarks.begin();

    while(it != m_landmarks.end())
    {
        if((*it)->get_name() == name)
        {
            m_landmarks.erase(it);

            return true;
        }

        it++;
    }

    return false;
}
