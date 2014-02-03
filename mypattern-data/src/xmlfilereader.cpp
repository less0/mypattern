#include "xmlfilereader.h"
#include "xmlexception.h"
#include <fstream>
#include <sstream>

using namespace MyPattern::Data;

XmlFileReader::XmlFileReader()
{
}

shared_ptr<PatternDefinition> XmlFileReader::read_pattern()
{
    shared_ptr<PatternDefinition> result(new PatternDefinition());

    Glib::ustring data = read_file(m_filename);

    shared_ptr<XmlNode> rootNode = XmlNode::parse(data);

    ///\todo restore pattern from XML-Tree

    if(rootNode->get_name() == "pattern")
    {
        list<XmlAttribute> parameters = rootNode->get_parameters();
        list<XmlAttribute>::iterator it_params = parameters.begin();

        if(it_params != parameters.end())
        {
            if(it_params->get_name() == "name")
            {
                result->set_name(it_params->get_value());
            }

            it_params++;
        }


        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        list<shared_ptr<XmlNode>>::iterator it_nodes = subnodes.begin();

        while(it_nodes != subnodes.end())
        {
            Glib::ustring subnode_name = (*it_nodes)->get_name();

            if(subnode_name == "part")
            {
                get_part((*it_nodes), result);
            }
            else if(subnode_name == "user")
            {
                // get the user whu created the pattern from XML-tree
            }
            else if(subnode_name == "measures")
            {
                //restore custom measures from XML-tree
            }


            it_nodes++;
        }
    }
    else
    {
        throw XmlException("Pattern files must contain a \"pattern\"-root-node");
    }

    return result;
}


Glib::ustring XmlFileReader::read_file(Glib::ustring filename)
{
    stringstream data;
    char* buffer;
    ifstream inputStream;

    inputStream.open(filename);

    if(!inputStream.is_open())
    {
        ///\todo throw exception
        return "";
    }

    streamoff start = inputStream.tellg();
    inputStream.seekg(0, ios::end);
    streamsize BUFFERSIZE = inputStream.tellg();
    inputStream.seekg(start);


    buffer = new char[BUFFERSIZE];

    inputStream.read(buffer, BUFFERSIZE);

    return Glib::ustring(buffer);
}

shared_ptr<PartDefinition> get_part(shared_ptr<XmlNode> node, shared_ptr<PatternDefinition> pattern)
{
    shared_ptr<PartDefinition> result = shared_ptr<PartDefinition>(new PartDefinition());

    list<XmlAttribute> attributes = node->get_parameters();
    list<XmlAttribute>::iterator it_attributes = attributes.begin();

    while(it_attributes != attributes.end())
    {
        switch((*it_attributes).get_name() == "name")
        {
            result->set_name((*it_attributes).get_value());
        }
    }

    return shared_ptr<PartDefinition>((PartDefinition*)NULL);
}

shared_ptr<Landmark> XmlFileReader::get_landmark(shared_ptr<XmlNode> node, shared_ptr<PartDefinition> part)
{
    return shared_ptr<Landmark>((Landmark*)NULL);
}

shared_ptr<CurveDefinition> XmlFileReader::get_curve(shared_ptr<XmlNode> node, shared_ptr<PartDefinition> part)
{
    return shared_ptr<CurveDefinition>((CurveDefinition*)NULL);
}

shared_ptr<PatternParameter> XmlFileReader::get_parameter(shared_ptr<XmlNode> node, shared_ptr<PatternDefinition> pattern)
{
    return shared_ptr<PatternParameter>((PatternParameter*)NULL);
}
