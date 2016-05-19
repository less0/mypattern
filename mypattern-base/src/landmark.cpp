#include "landmark.h"
#include "evaluation/formula/term.h"
#include "exceptions/formulaevaluationexception.h"
#include "exceptions/argumentexception.h"



#include <sstream>
#include <iostream>
#include <string>

using namespace std;

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


bool Landmark::set_name(string name)
{
    sigc::signal1<bool, string>::slot_list_type slots =
        this->signal_name_change_request.slots();

    bool has_slots = slots.begin() != slots.end();

    string old_name = this->m_name;

    if(!has_slots || this->signal_name_change_request.emit(name))
    {
        this->m_name = name;

        return true;
    }

    return false;
}

string Landmark::get_name()
{
    return m_name;
}


bool Landmark::set_definition_x(string definition)
{
    shared_ptr<Term> new_x_term;
    new_x_term = Term::parse(definition);


    list<string> new_dependencies = depends_on(new_x_term->get_symbol_names(), m_y_term->get_symbol_names(), true);

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

string Landmark::get_definition_x()
{
    return this->m_x_definition;
}

bool Landmark::set_definition_y(string definition)
{
    shared_ptr<Term> new_y_term = Term::parse(definition);

    list<string> new_dependencies = depends_on(m_x_term->get_symbol_names(), new_y_term->get_symbol_names(), true);

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


string Landmark::get_definition_y()
{
    return this->m_y_definition;
}

list<string> Landmark::depends_on(bool strip_argument)
{
    list<string> dependencies_x = m_x_term->get_symbol_names();
    list<string> dependencies_y = m_y_term->get_symbol_names();

    return depends_on(dependencies_x, dependencies_y, strip_argument);
}

list<string> Landmark::depends_on(list<string> dependencies_x, list<string> dependencies_y, bool strip_argument)
{
    list<string> dependencies;
    list<string>::iterator it;

    for(it = dependencies_x.begin(); it != dependencies_x.end(); it++)
    {
        bool found_in_list = false;
        string current_dependency = *it;


	if(strip_argument)
	{
        	//strip argument
        	string::size_type index_of_bracket;

        	if((index_of_bracket = current_dependency.find('[')) != string::npos)
        	{
        	    current_dependency = current_dependency.substr(0, index_of_bracket);
        	}
	}

        for(list<string>::iterator it2 = dependencies.begin(); it2 != dependencies.end(); it2++)
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
        string current_dependency = *it;

		if(strip_argument)
		{
			//strip argument
			string::size_type index_of_bracket;

			if((index_of_bracket = current_dependency.find('[')) != string::npos)
			{
				current_dependency = current_dependency.substr(0, index_of_bracket);
			}
		}

        for(list<string>::iterator it2 = dependencies.begin(); it2 != dependencies.end(); it2++)
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

Point Landmark::get_point(map<string,double> values)
{
	Point result = Point(m_x_term->evaluate(values), m_y_term->evaluate(values));
	result.set_landmark_name(m_name);
	return result;
}

shared_ptr<Landmark> Landmark::deserialize_from_xml(shared_ptr<XmlNode> node)
{
	if(node->get_name() != "landmark")
	{
		throw ArgumentException("Wrong node type");
	}
	
	bool parsedName = false;
	bool parsedXDefinition = false;
	bool parsedYDefinition = false;

	shared_ptr<Landmark> parsedLandmark = shared_ptr<Landmark>(new Landmark());
	
	list<XmlAttribute> attributes = node->get_attributes();
	for(list<XmlAttribute>::iterator it = attributes.begin();
		it != attributes.end();
		it++)
	{
		if(it->get_name() == "name")
		{
			if(it->get_value() == "")
			{
				throw ArgumentException("Empty landmark name");
			}
		
			parsedLandmark->set_name(it->get_value());
			parsedName = true;
		}
		else if(it->get_name() == "x")
		{
			if(it->get_value() == "")
			{
				throw ArgumentException("Empty landmark x definition");
			}
		
			parsedLandmark->set_definition_x(it->get_value());
			parsedXDefinition = true;
		}
		else if(it->get_name() == "y")
		{
			if(it->get_value() == "")
			{
				throw ArgumentException("Empty landmark y definition");
			}
			
			parsedLandmark->set_definition_y(it->get_value());
			parsedYDefinition = true;
		}
	}
	
	if(!parsedXDefinition
		|| !parsedYDefinition
		|| !parsedName)
	{
		throw ArgumentException("Incomplete landmark");
	}

	return parsedLandmark;
}
