#include "xmlnode.h"

#include <sstream>
#include <exception.h>

using namespace MyPattern::Data;
using namespace MyPattern::Exceptions;

XmlNode::XmlNode()
{
    //ctor
}

XmlNode::XmlNode(Glib::ustring name)
{
    m_name = name;
}

XmlNode::XmlNode(const XmlNode& base)
{
    m_name = base.m_name;

    list<XmlAttribute>::const_iterator it = base.m_parameters.begin();

    while(it != base.m_parameters.end())
    {
        m_parameters.push_back(*it);
        it++;
    }
}

shared_ptr<XmlNode> XmlNode::parse(Glib::ustring schema)
{
    shared_ptr<XmlNode> result(new XmlNode());
    //int subschema_index = 0;
    Glib::ustring subschema = "";
    list<Glib::ustring> ls_nodes;

    int start_tag_index = schema.find_first_of('<');
    Glib::ustring tag = get_tag(schema, start_tag_index);

    int firstSpaceIndex = schema.find_first_of(' ');
    int closingBracket = schema.find('>', start_tag_index);



    Glib::ustring tag_name = schema.substr(start_tag_index + 1,
                                           (firstSpaceIndex < 0 || firstSpaceIndex>closingBracket ? closingBracket :  firstSpaceIndex) - start_tag_index - 1);

    result->m_name = tag_name;
    ///\todo parse key value pairs
    result->m_parameters = XmlAttribute::parse_from_tag(tag);

    if(tag_is_terminated(Glib::ustring(tag)))
    {
        return result;
    }

    stringstream end_tag_builder;
    end_tag_builder << "</"
        << tag_name
        << ">";

    int end_tag_index = schema.find(end_tag_builder.str(), start_tag_index);

    subschema = schema.substr(start_tag_index + tag.length(),
                              end_tag_index - start_tag_index - tag.length());

    ls_nodes = split_nodes(subschema);

    list<Glib::ustring>::iterator it = ls_nodes.begin();

    while(it != ls_nodes.end())
    {
        result->m_subnodes.push_back(XmlNode::parse(*it));
        it++;
    }


    return result;
}

list<shared_ptr<XmlNode>> XmlNode::parse_subnodes(Glib::ustring schema, Glib::ustring parent_node_name, int start_index, int& end_index)
{
    //Notizen:
    //The present function is quite lengthy, with many

    list<shared_ptr<XmlNode>> parsedNodes;

    bool inNode = false;
    bool inElement = false;
    bool inElementName = false;
    bool inAttribute = false;
    bool inAttributeValue = false;

    Glib::ustring currentNodeName = "";
    Glib::ustring currentElementName = "";
    bool isEndElement = false;

    int elementStartIndex = 0;
    int slashIndex = 0;

    bool finishedParsing = false;
    int currentIndex = 0;

    while(!finishedParsing && currentIndex < schema.length())
    {
        if(schema[currentIndex] == '<')
        {
            if(!inAttributeValue && !inElement)
            {
                inElement = true;
                inElementName = true;
                elementStartIndex = currentIndex;
            }
            else if(inElement)
            {
                throw MyPattern::Exceptions::Exception();
                //Exception("Unexpected character '<' in element");
            }

        }
        else if(schema[currentIndex] == '"')
        {
            if(inAttribute && !inAttributeValue)
            {
                inAttributeValue = true;
            }
            else if(inAttributeValue)
            {
                inAttributeValue = false;
            }
            else if(!inElement)
            {
                throw MyPattern::Exceptions::Exception("");
            }
        }
        else if(schema[currentIndex] == '>')
        {
            if(!inAttributeValue)
            {
                //bracket is within an attribute value and thus ignored
            }
            else if(inElement)
            {
                inElement = false;
                inElementName = false;
                inAttribute = false;

                //there has been a slash within the current element
                if(slashIndex > elementStartIndex)
                {
                    if(slashIndex == elementStartIndex + 1)
                    {
                        //element is end element


                        //compare name with node name

                        //if the name mateches the current node name
                    }
                    else if(slashIndex == elementStartIndex - 1)
                    {
                        //element is self ended
                    }
                    else
                    {
                        //the slash has been placed neither at the begging, nor
                        // at the end of the element. This is an unexpected
                        //form, therefor an Exception will be thrown
                    }
                }
                else
                {
                    //there hab been no slash

                    //if there is a current node start subnodes now

                    //else create new current node
                }

                /*! \todo implement logic */


            }
        }
        else if(schema[currentIndex] == '/')
        {
            if(inElement)
            {
                slashIndex = currentIndex;
            }
        }
        else if(schema[currentIndex] == ' ')
        {
            if(inElementName)
            {
                inElementName = false;
            }
            else if(inAttribute)
            {
                inAttribute = false;
            }
        }
        else if(schema[currentIndex] == ' ')
        {
        }
        else
        {
            if(inElementName)
            {
                //check for valid characters for element names here

                //else throw exception
            }
            else if(inElement &&  !inAttributeValue)
            {

            }

        }

        currentIndex++;
    }

    end_index = currentIndex;

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

list<XmlAttribute> XmlNode::get_parameters()
{
    return this->m_parameters;
}

bool XmlNode::add_parameter(XmlAttribute param)
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

bool XmlNode::remove_parameter(XmlAttribute param)
{
    return this->remove_parameter(param.get_name());
}

bool XmlNode::remove_parameter(Glib::ustring name)
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
