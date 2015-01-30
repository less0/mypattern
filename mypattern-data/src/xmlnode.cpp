#include "xmlnode.h"

#include <sstream>
#include <iostream>
#include <exception.h>
#include <xmlelement.h>
#include <xmlexception.h>

using namespace MyPattern::Data;
using namespace MyPattern::Exceptions;

XmlNode::XmlNode()
{
    //ctor
}

XmlNode::XmlNode(Glib::ustring name)
{
    m_name = name;
	m_text = "";
}

XmlNode::XmlNode(const XmlNode& base)
{
    m_name = base.m_name;
	m_text = base.m_text;

    list<XmlAttribute>::const_iterator it = base.m_parameters.begin();

    while(it != base.m_parameters.end())
    {
        m_parameters.push_back(*it);
        it++;
    }
}

shared_ptr<XmlNode> XmlNode::parse(Glib::ustring schema)
{
	int end_index;

    return parse_node(schema, 0, end_index);
}

shared_ptr<XmlNode> XmlNode::parse_node(Glib::ustring schema, int start_index, int& end_index)
{
	shared_ptr<XmlNode> result(new XmlNode());
    // Glib::ustring subschema = "";
    list<shared_ptr<XmlNode>> ls_nodes;

    // int start_tag_index = schema.find_first_of('<'); //not 100% XML compliant
    int end_element_index = 0;
    XmlElement start_element = XmlElement::parse_element(schema, start_index, end_element_index);

	
    result->m_name = start_element.GetName();
    result->m_parameters = start_element.GetAttributes();

    if(start_element.isEmpty())
    {
        return result;
    }

	int end_end_tag = 0;
    int end_subnodes = 0;
	ustring node_text = "";
	
    ls_nodes = parse_subnodes(schema, start_element.GetName(), end_element_index+1, end_subnodes, node_text);

	XmlElement endElement = XmlElement::parse_element(schema, end_subnodes+1, end_end_tag);
	
	
	end_index = end_end_tag;
	
	result->set_text(node_text);
    result->m_subnodes = ls_nodes;
	
	return result;
}

list<shared_ptr<XmlNode>> XmlNode::parse_subnodes(Glib::ustring schema, Glib::ustring parent_node_name, int start_index, int& end_index, ustring& text)
{
    list<shared_ptr<XmlNode>> parsedNodes;
    shared_ptr<XmlNode> current_node;
    int current_index = start_index;
    bool run = true; // states
	text = "";

	
	
    while(run)
    {
        int next_index = current_index;
		
        if(schema[current_index] == '<')
        {
            XmlElement element = XmlElement::parse_element(schema, current_index, next_index);

            if(element.isEndElement())
            {
				if(parent_node_name == element.GetName())
                {
                    end_index = current_index - 1;
                    run=false;
                }
                else
                {
                    throw XmlException("Unexpected end-tag");
                }
            }
            else //element is start element
            {
				current_node = parse_node(schema, current_index, next_index);
				parsedNodes.push_back(current_node);
            }
        }
        else
        {
			text += schema[current_index];
        }
        current_index = next_index + 1;
    }

    return parsedNodes;
}

///\brief splits a string by XML nodes
list<Glib::ustring> XmlNode::split_nodes(Glib::ustring subschema)
{
    int node_begin = subschema.find_first_of('<');

    list<Glib::ustring> nodes;

    while(node_begin >= 0 && node_begin < (int)subschema.length())
    {
        int node_name_end = -1;

        int first_space_index = subschema.find(' ', node_begin);
        int closing_bracket_index = subschema.find('>', node_begin);

        if(first_space_index < 0 || closing_bracket_index < first_space_index)
        {
            node_name_end = closing_bracket_index;
        }
        else
        {
            node_name_end = first_space_index;
        }

        if(node_name_end < 0)
        {
            return list<Glib::ustring>();
        }

        Glib::ustring node_name = subschema.substr(node_begin + 1, node_name_end - node_begin - 1);

        if(node_name.length() == 0)
        {
            return list<Glib::ustring>();
        }

        Glib::ustring tag = get_tag(subschema, node_begin);

        if(tag_is_terminated(tag))
        {
            nodes.push_back(tag);
            node_begin = subschema.find('<', node_begin + tag.length());
        }
        else
        {
            stringstream end_tag;
            end_tag << "</";
            end_tag << node_name;
            end_tag << ">";

            int node_end_index = subschema.find(end_tag.str(), node_begin) + end_tag.str().length();
            nodes.push_back(subschema.substr(node_begin, node_end_index - node_begin));
            node_begin = subschema.find('<', node_end_index);
        }
    }

    return nodes;
}

Glib::ustring XmlNode::get_tag(Glib::ustring schema, int index)
{
    int start_index = schema.find('<', index);
    int end_index = schema.find('>', start_index);

    return schema.substr(start_index, end_index - start_index + 1);
}

bool XmlNode::tag_is_terminated(Glib::ustring tag)
{
    if(tag[tag.length() - 2] == '/')
    {
        return true;
    }
    else
        return false;
}

Glib::ustring XmlNode::get_name()
{
    return this->m_name;
}

void XmlNode::set_name(Glib::ustring name)
{
    this->m_name = name;
}

list<shared_ptr<XmlNode>> XmlNode::get_nodes()
{
    return this->m_subnodes;
}

list<XmlAttribute> XmlNode::get_attributes()
{
    return this->m_parameters;
}

bool XmlNode::add_attribute(XmlAttribute param)
{
    list<XmlAttribute>::iterator it = this->m_parameters.begin();

    while(it != this->m_parameters.end())
    {
        if((*it).get_name() == param.get_name())
        {
            return false;
        }

        it++;
    }

    this->m_parameters.push_back(XmlAttribute(param));
    return true;
}

bool XmlNode::remove_attribute(XmlAttribute param)
{
    return this->remove_attribute(param.get_name());
}

bool XmlNode::remove_attribute(Glib::ustring name)
{
    list<XmlAttribute>::iterator it = this->m_parameters.begin();

    while(it != this->m_parameters.end())
    {
        if((*it).get_name() == name)
        {
            ///\todo remove element from list
            //this->m_parameters.remove(*it);
            return true;
        }

        it++;
    }

    return false;
}

void XmlNode::add_node(shared_ptr<XmlNode> nodeToAdd)
{
    m_subnodes.push_back(nodeToAdd);
}

Glib::ustring XmlNode::get_text()
{
    return m_text;
}

void XmlNode::set_text(Glib::ustring text)
{
	m_text = text;
}