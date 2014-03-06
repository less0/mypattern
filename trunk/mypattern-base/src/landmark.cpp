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

    //initialize definitions to (0,0)
    Landmark::m_x_definition = "0";
    Landmark::m_x_term = Term::parse(m_x_definition);

    Landmark::m_y_definition = "0";
    Landmark::m_y_term = Term::parse(m_y_definition);

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
    shared_ptr<Term> new_x_term;
    new_x_term = Term::parse(definition);


    list<ustring> new_dependencies = depends_on(new_x_term->get_symbol_names(), m_y_term->get_symbol_names(), true);

    if(signal_change_request.empty() || signal_change_request(new_dependencies))
    {
        this->m_x_definition = definition;
        this->m_x_term = new_x_term;

        if(!signal_changed.empty())
        {
            signal_changed();
        }

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

    list<ustring> new_dependencies = depends_on(m_x_term->get_symbol_names(), new_y_term->get_symbol_names(), true);

    if(signal_change_request.empty() || signal_change_request(new_dependencies))
    {
        this->m_y_definition = definition;
        this->m_y_term = new_y_term;

        if(!signal_changed.empty())
        {
            this->signal_changed();
        }

        return true;
    }

    return false;
}


Glib::ustring Landmark::get_definition_y()
{
    return this->m_y_definition;
}

list<ustring> Landmark::depends_on(bool strip_argument)
{
    list<ustring> dependencies_x = m_x_term->get_symbol_names();
    list<ustring> dependencies_y = m_y_term->get_symbol_names();

    return depends_on(dependencies_x, dependencies_y, strip_argument);
}

list<Glib::ustring> Landmark::depends_on(list<ustring> dependencies_x, list<ustring> dependencies_y, bool strip_argument)
{
    list<ustring> dependencies;
    list<ustring>::iterator it;

    for(it = dependencies_x.begin(); it != dependencies_x.end(); it++)
    {
        bool found_in_list = false;
        ustring current_dependency = *it;


	if(strip_argument)
	{
        	//strip argument
        	ustring::size_type index_of_bracket;

        	if((index_of_bracket = current_dependency.find('[')) != string::npos)
        	{
        	    current_dependency = current_dependency.substr(0, index_of_bracket);
        	}
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

		if(strip_argument)
		{
			//strip argument
			ustring::size_type index_of_bracket;

			if((index_of_bracket = current_dependency.find('[')) != string::npos)
			{
				current_dependency = current_dependency.substr(0, index_of_bracket);
			}
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

Point Landmark::get_point(map<ustring,double> values)
{
	return Point(m_x_term->evaluate(values), m_y_term->evaluate(values));
}
