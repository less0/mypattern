#include "xmlfilereader.h"
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
        list<XmlParameter> parameters = rootNode->get_parameters();
        list<XmlParameter>::iterator it_params = parameters.begin();

        if(it_params != parameters.end())
        {
            switch(it_params->get_name())
            {
                case "name":
                    result->set_name(it_params.get_value());
                    break;
            }

            it_params++;
        }


        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        list<shared_ptr<XmlNode>>::iterator it_nodes = subnodes.begin();

        while(it_nodes != subnodes.end())
        {
            switch((*it_nodes)->get_name())
            {
                case "part":
                    get_part((*it_nodes), result);
                    break;
                case "user":
                    break;
            }
            it_nodes++;
        }
    }
    else
    {
        ///\todo Throw exception
        return shared_ptr<PatternDefinition>((PatternDefinition*)NULL);
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

}

shared_ptr<Landmark> XmlFileReader::get_landmark(shared_ptr<XmlNode> node, shared_ptr<PartDefinition> part)
{

}

shared_ptr<CurveDefinition> XmlFileReader::get_curve(shared_ptr<XmlNode> node, shared_ptr<PartDefinition> part)
{

}

shared_ptr<PatternParameter> XmlFileReader::get_parameter(shared_ptr<XmlNode> node, shared_ptr<PatternDefinition> pattern)
{

}
