#include "patterndefinition.h"

#include "patternerror.h"

#include <iostream>
#include <fstream>

using namespace MyPattern::Base;

PatternDefinition::PatternDefinition()
{
    this->m_name = "";
}

PatternDefinition::PatternDefinition(Glib::ustring name)
{
    this->set_name(name);
}

Pattern PatternDefinition::get_pattern(Measures measures)
{
    return get_pattern(measures, list<PatternParameterValue>());
}

Pattern PatternDefinition::get_pattern(Measures measures, list<PatternParameterValue> parameter_values)
{
    Pattern pattern = Pattern();

    pattern.set_name(this->get_name());

    list<shared_ptr<PartDefinition>>::iterator it = this->m_part_definitions.begin();

    while(it != this->m_part_definitions.end())
    {
        pattern.add_part((**it).get_part());

        it++;
    }

    return pattern;
}

shared_ptr<PatternDefinition> PatternDefinition::read_xml(Glib::ustring filename)
{
    XmlFileReader filereader = XmlFileReader();

    filereader.read(filename);
    shared_ptr<XmlNode> root_node = filereader.get_root_node();

    return shared_ptr<PatternDefinition>(NULL);
}

//bool PatternDefinition::write_xml(Glib::ustring filename)
//{
//    std::ofstream output_stream;
//    list<shared_ptr<PatternParameter>>::iterator it_parameters;
//    list<shared_ptr<PartDefinition>>::iterator it_parts;
//
//    output_stream.open(filename);
//
//    if(!output_stream.is_open())
//    {
//        return false;
//    }
//
//    output_stream << "<pattern name=\"" << this->m_name << "\">" << endl;
//
//    it_parameters = this->m_pattern_parameters.begin();
//
//    while(it_parameters != this->m_pattern_parameters.end())
//    {
//        output_stream << (**it_parameters).get_xml();
//
//        it_parameters++;
//    }
//
//    it_parts = this->m_part_definitions.begin();
//
//    while(it_parts != this->m_part_definitions.end())
//    {
//        output_stream << (**it_parts).get_xml();
//
//        it_parts++;
//    }
//
//    output_stream << "</pattern>";
//
//    output_stream.close();
//
//    return true;
//}

shared_ptr<PartDefinition> PatternDefinition::create_part_definition(Glib::ustring name)
{
    shared_ptr<PartDefinition> part_definition(new PartDefinition());
    part_definition->set_name(name);

    if(!this->add_part_definition(part_definition))
    {
        return shared_ptr<PartDefinition>(NULL);
    }

    return part_definition;
}

bool PatternDefinition::add_part_definition(shared_ptr<PartDefinition> part_definition)
{
    list<shared_ptr<PartDefinition>>::iterator it = this->m_part_definitions.begin();

    while(it != this->m_part_definitions.end())
    {
        if((*it)->get_name() == part_definition->get_name())
        {
            return false;
        }

        it++;
    }

    //connect part definitions event on name change
    part_definition->signal_name_change_request().connect(sigc::mem_fun(this,
        &PatternDefinition::on_name_change_request));
    this->m_part_definitions.push_back(part_definition);

    return true;
}

shared_ptr<PartDefinition> PatternDefinition::get_part_definition(Glib::ustring name)
{
    list<shared_ptr<PartDefinition>>::iterator it = this->m_part_definitions.begin();

    while(it != this->m_part_definitions.end())
    {
        if((*it)->get_name() == name)
        {
            return *it;
        }
    }

    return shared_ptr<PartDefinition>(NULL);
}

shared_ptr<PartDefinition> PatternDefinition::get_part_definition(unsigned long index)
{
    if(index >= this->m_part_definitions.size())
    {
        return shared_ptr<PartDefinition>(NULL);
    }

    list<shared_ptr<PartDefinition>>::iterator it = this->m_part_definitions.begin();

    while(index > 0)
    {
        it++;
        index--;
    }

    return *it;
}

list<shared_ptr<PartDefinition>> PatternDefinition::get_part_definitions()
{
    return this->m_part_definitions;
}

bool PatternDefinition::add_pattern_parameter(shared_ptr<PatternParameter> parameter)
{
    list<shared_ptr<PatternParameter>>::iterator it = this->m_pattern_parameters.begin();

    while(it != this->m_pattern_parameters.end())
    {
        if((**it).get_name() == parameter->get_name())
        {
            return false;
        }

        it++;
    }

    this->m_pattern_parameters.push_back(parameter);

    return true;
}

list<Glib::ustring> PatternDefinition::get_part_defintion_names()
{
    list<Glib::ustring> names;
    list<shared_ptr<PartDefinition>>::iterator it = this->m_part_definitions.begin();

    while(it != m_part_definitions.end())
    {
        names.push_back((*it)->get_name());
        it++;
    }

    return names;
}

list<Glib::ustring> PatternDefinition::get_pattern_parameter_names()
{
    list<Glib::ustring> names;

    list<shared_ptr<PatternParameter>>::iterator it = this->m_pattern_parameters.begin();

    while(it != this->m_pattern_parameters.end())
    {
        names.push_back((*it)->get_name());
        it++;
    }

    return names;
}

shared_ptr<PatternParameter> PatternDefinition::get_pattern_parameter(Glib::ustring name)
{
    list<shared_ptr<PatternParameter>>::iterator it =  this->m_pattern_parameters.begin();

    while(it != this->m_pattern_parameters.end())
    {
        if((*it)->get_name() == name)
        {
            return *it;
        }

        it++;
    }

    return shared_ptr<PatternParameter>(NULL);
}

list<shared_ptr<PatternParameter>> PatternDefinition::get_pattern_parameters()
{
    return this->m_pattern_parameters;
}

bool PatternDefinition::remove_pattern_parameter(Glib::ustring name)
{
    list<shared_ptr<PatternParameter>>::iterator it = this->m_pattern_parameters.begin();

    while(it != this->m_pattern_parameters.end())
    {
        if((*it)->get_name() == name)
        {
            this->m_pattern_parameters.remove(*it);
            return true;
        }
    }

    return false;
}

shared_ptr<User> PatternDefinition::get_author()
{
    return this->m_author;
}

void PatternDefinition::set_author(shared_ptr<User> author)
{
    this->m_author = author;
}

int PatternDefinition::get_version()
{
    return this->m_version;
}

void PatternDefinition::set_version(int version)
{
    this->m_version = version;
}

int PatternDefinition::get_revision()
{
    return this->m_revision;
}

void PatternDefinition::set_revision(int revision)
{
    this->m_revision = revision;
}

Glib::ustring PatternDefinition::get_name()
{
    return this->m_name;
}

void PatternDefinition::set_name(Glib::ustring name)
{
    this->m_name = name;
}

Glib::ustring PatternDefinition::get_uid()
{
    return this->m_uid;
}

void PatternDefinition::set_uid(Glib::ustring uid)
{
    this->m_uid = uid;
}

bool PatternDefinition::on_name_change_request(Glib::ustring name)
{
    list<shared_ptr<PartDefinition>>::iterator it = m_part_definitions.begin();

    while(it != m_part_definitions.end())
    {
        if((*it)->get_name() == name)
        {
            return false;
        }
        it++;
    }

    return true;
}
