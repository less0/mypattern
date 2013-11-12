#include "landmark.h"

#include <sstream>
#include <glibmm/regex.h>

using namespace MyPattern::Base;

Landmark::Landmark()
{
    m_name = "";
    m_x_definition = "";
    m_y_definition = "";
}

Landmark::~Landmark()
{
    //dtor
}


bool Landmark::set_name(Glib::ustring name)
{
    sigc::signal2<bool, Glib::ustring,ObjectType>::slot_list_type slots =
        this->m_signal_name_change_request.slots();
    sigc::signal2<bool, Glib::ustring, ObjectType>::slot_list_type::iterator it =
        slots.begin();

    bool has_slots = false;

    while(it != slots.end())
    {
        has_slots = true;
        it++;
    }

    Glib::ustring old_name = this->m_name;

    if(!has_slots || this->m_signal_name_change_request.emit(name, ObjectType::PARTTYPE_LANDMARK))
    {
        this->m_name = name;
        this->m_signal_name_changed.emit(shared_ptr<Landmark>(this), old_name);
        return true;
    }

    return false;
}

Glib::ustring Landmark::get_name()
{
    return this->m_name;
}

bool Landmark::set_definition_x(Glib::ustring definition)
{
//    if(validate_definition(definition))
//    {
        this->m_x_definition = definition;

        //this->m_signal_changed.emit(shared_ptr<Landmark>(this));
        //this->m_signal_changed.emit(shared_ptr<Landmark>(this));

        return true;
//    }

    return false;
}

Glib::ustring Landmark::get_definition_x()
{
    return this->m_x_definition;
}

bool Landmark::set_definition_y(Glib::ustring definition)
{
    if(validate_definition(definition))
    {
        this->m_y_definition = definition;

        //this->m_signal_changed.emit(shared_ptr<Landmark>(this));

        return true;
    }

    return false;
}

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

list<Glib::ustring> Landmark::depends_on()
{
    list<Glib::ustring> dependencies;

    Glib::ustring pattern_landmark = "\\$[A-Za-z]{1,}\\.[XYxy]{1,1}";
    Glib::ustring pattern_measure = "#[A-Za-z]{1,}";
    Glib::ustring pattern_parameter = "@[A-Za-z]{1,}";

    Glib::RefPtr<Glib::Regex> landmark_regex = Glib::Regex::create(pattern_landmark,
                                                                   (Glib::RegexCompileFlags)0,
                                                                   (Glib::RegexMatchFlags)0);
    Glib::RefPtr<Glib::Regex> measure_regex = Glib::Regex::create(pattern_measure,
                                                                    Glib::RegexCompileFlags(0),
                                                                    (Glib::RegexMatchFlags)0);
    Glib::RefPtr<Glib::Regex> parameter_regex = Glib::Regex::create(pattern_parameter,
                                                                    (Glib::RegexCompileFlags)0,
                                                                    (Glib::RegexMatchFlags)0);

    Glib::MatchInfo matchInfo;

    landmark_regex->match(this->m_x_definition, matchInfo);

    while(matchInfo.matches())
    {
        dependencies.push_back(matchInfo.fetch(0));
        matchInfo.next();
    }

    Glib::MatchInfo landmark_match_info_y;

    landmark_regex->match(this->m_y_definition, landmark_match_info_y);
//
    while(landmark_match_info_y.matches())
    {
        dependencies.push_back(landmark_match_info_y.fetch(0));
        landmark_match_info_y.next();
    }

    Glib::MatchInfo measure_match_info_x;
    measure_regex->match(this->m_x_definition, measure_match_info_x);

    while(measure_match_info_x.matches())
    {
        dependencies.push_back(measure_match_info_x.fetch(0));
        measure_match_info_x.next();
    }

    Glib::MatchInfo measure_match_info_y;
    measure_regex->match(this->m_y_definition, measure_match_info_y);

    while(measure_match_info_y.matches())
    {
        dependencies.push_back(measure_match_info_y.fetch(0));
        measure_match_info_y.next();
    }

    Glib::MatchInfo parameter_match_info_x;
    parameter_regex->match(this->m_x_definition, parameter_match_info_x);

    while(parameter_match_info_x.matches())
    {
        dependencies.push_back(parameter_match_info_x.fetch(0));
        parameter_match_info_x.next();
    }

    Glib::MatchInfo parameter_match_info_y;
    parameter_regex->match(this->m_y_definition, parameter_match_info_y);

    while(parameter_match_info_y.matches())
    {
        dependencies.push_back(parameter_match_info_y.fetch(0));
        parameter_match_info_y.next();
    }

    return dependencies;
}

sigc::signal1<void, shared_ptr<Landmark>> Landmark::signal_changed()
{
    return this->m_signal_changed;
}

sigc::signal2<void, shared_ptr<Landmark>, Glib::ustring> Landmark::signal_name_changed()
{
    return this->m_signal_name_changed;
}

//Glib::ustring Landmark::get_xml()
//{
//    stringstream result;
//
//    result << "<landmark name=\"" + get_name() + "\" ";
//    result << "x=\"" + get_definition_x() + "\" ";
//    result << "y=\"" + get_definition_y() + "\" ";
//    result << " />" << std::endl;
//
//    return Glib::ustring(result.str());
//}

