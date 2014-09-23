#include "xmlfilereader.h"
#include "xmlexception.h"
#include "exceptions/filenotfoundexception.h"
#include <fstream>
#include <sstream>

using namespace MyPattern::Data;
using namespace MyPattern::Data::Exceptions;

XmlFileReader::XmlFileReader()
{
    m_root_node = nullptr;
    m_raw_xml = "";
}

void XmlFileReader::read(Glib::ustring filename)
{
    m_raw_xml = read_file(filename);
}

shared_ptr<XmlNode> XmlFileReader::get_root_node()
{
    if(m_root_node == NULL)
    {
        m_root_node = XmlNode::parse(m_raw_xml);
    }

    return m_root_node;
}

Glib::ustring XmlFileReader::read_file(Glib::ustring filename)
{
    stringstream data;
    char* buffer;
    ifstream inputStream;

    inputStream.open(filename);

    if(!inputStream.is_open())
    {
        throw FileNotFoundException();
    }

    streamoff start = inputStream.tellg();
    inputStream.seekg(0, ios::end);
    streamsize BUFFERSIZE = inputStream.tellg();
    inputStream.seekg(start);


    buffer = new char[BUFFERSIZE];

    inputStream.read(buffer, BUFFERSIZE);

    return Glib::ustring(buffer);
}
