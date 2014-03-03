#include "landmark.h"
#include "evaluation/formula/term.h"
#include "exceptions/formulaevaluationexception.h"


#include <sstream>
#include <iostream>
#include <glibmm/regex.h>


using namespace MyPattern::Base;
using namespace MyPattern::Base::Evaluation::Formula;
using namespace MyPattern::Exceptions;

Landmark::Landmark() : PatternObject(OBJECTTYPE_LANDMARK)
{
    m_name = "";
    set_definition_x("0");
    set_definition_y("0");
}

Landmark::~Landmark()
{
    //dtor
}


bool Landmark::set_name(Glib::ustring name)
{
    sigc::signal1<bool, Glib::ustring>::slot_list_type slots =
        this->signal_name_change_request.slots();

    bool has_slots = slots.begin() != slots.end();

    Glib::ustring old_name = this->m_name;

    if(!has_slots || this->signal_name_change_request.emit(name))
    {
        this->m_name = name;

        //this->m_signal_name_changed.emit(shared_ptr<Landmark>(this), old_name);

        return true;
    }

    return false;
}

Glib::ustring Landmark::get_name()
{
    return m_name;
}

bool Landmark::set_definition_x(Glib::ustring definition)
{
    shared_ptr<Term> parsed_term;

    try
    {
        parsed_term = Term::parse(definition);
    }
    catch(FormulaEvaluationException e)
    {
        return false;
    }

    if(validate_definition(definition))
    {
        this->m_x_definition = definition;
        this->m_x_term = parsed_term;

        //this->m_signal_changed.emit(shared_ptr<Landmark>(this));

        return true;
    }

    return false;
}

Glib::ustring Landmark::get_definition_x()
{
    return this->m_x_definition;
}

bool Landmark::set_definition_y(Glib::ustring definition)
{
    shared_ptr<Term> new_y_term = Term::parse(definition);

    list<ustring> new_dependencies = depends_on(m_x_term->get_symbol_names(), new_y_term->get_symbol_names());

    signal1<bool, list<ustring>>::slot_list_type slots =
        signal_change_request.slots();

    bool has_slots = !(slots.begin() == slots.end());

    if(!has_slots || signal_change_request(new_dependencies))
    {
        this->m_y_definition = definition;
        this->m_y_term = new_y_term;

        signal0<void>::slot_list_type signal_changed_slots = this->signal_changed.slots();

        if(signal_changed_slots.begin() != signal_changed_slots.end())
        {
            this->signal_changed();
        }

        return true;
    }

    return false;
}

//void Landmark::connect_change_request(sigc::slot<bool, list<ustring>> slot)
//{
//    Landmark::m_signal_change_request.connect(slot);
//}

/*! \todo Implement
*/
bool Landmark::validate_definition(Glib::ustring definition)
{
    return  true;
}

Glib::ustring Landmark::get_definition_y()
{
    return this->m_y_definition;
}

list<ustring> Landmark::depends_on()
{
    list<ustring> dependencies_x = m_x_term->get_symbol_names();
    list<ustring> dependencies_y = m_y_term->get_symbol_names();

    return depends_on(dependencies_x, dependencies_y);
}

list<Glib::ustring> Landmark::depends_on(list<ustring> dependencies_x, list<ustring> dependencies_y)
{
    list<ustring> dependencies;
    list<ustring>::iterator it;

    for(it = dependencies_x.begin(); it != dependencies_x.end(); it++)
    {
        bool found_in_list = false;
        ustring current_dependency = *it;

        //strip argument
        ustring::size_type index_of_bracket;

        if((index_of_bracket = current_dependency.find('[')) != string::npos)
        {
            current_dependency = current_dependency.substr(0, index_of_bracket);
        }

        for(list<ustring>::iterator it2 = dependencies.begin(); it2 != dependencies.end(); it2++)
        {
            if(*it2 == current_dependency)
            {
                found_in_list = true;
                break;
            }
        }

        if(!found_in_list)
        {
            dependencies.push_back(current_dependency);
        }
    }

    for(it = dependencies_y.begin(); it != dependencies_y.end(); it++)
    {
        bool found_in_list = false;
        ustring current_dependency = *it;

        //strip argument
        ustring::size_type index_of_bracket;

        if((index_of_bracket = current_dependency.find('[')) != string::npos)
        {
            current_dependency = current_dependency.substr(0, index_of_bracket);
        }

        for(list<ustring>::iterator it2 = dependencies.begin(); it2 != dependencies.end(); it2++)
        {
            if(*it2 == current_dependency)
            {
                found_in_list = true;
                break;
            }
        }

        if(!found_in_list)
        {
            dependencies.push_back(current_dependency);
        }
    }

    return dependencies;
}

//void Landmark::add_observer(shared_ptr<EvaluationTreeObserver> observer)
//{
//    for(list<shared_ptr<EvaluationTreeObserver>>::iterator it = m_observers.begin(); it!=m_observers.end(); it++)
//    {
//        if(observer == *it)
//        {
//            return;
//        }
//    }
//
//    m_observers.push_back(observer);
//}
//
//void Landmark::remove_observer(shared_ptr<EvaluationTreeObserver> observer)
//{
//    for(list<shared_ptr<EvaluationTreeObserver>>::iterator it = m_observers.begin(); it!=m_observers.end(); it++)
//    {
//        if(observer == *it)
//        {
//            m_observers.remove(*it);
//
//            return;
//        }
//    }
//}

//sigc::signal1<void, shared_ptr<Landmark>> Landmark::signal_changed()
//{
//    return this->m_signal_changed;
//}
//
//sigc::signal2<void, shared_ptr<Landmark>, Glib::ustring> Landmark::signal_name_changed()
//{
//    return this->m_signal_name_changed;
//}
