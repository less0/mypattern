#include <iostream>

#include "xmlnode.h"

int main()
{
    int in;
    shared_ptr<XmlNode> xmlNode = XmlNode::parse(Glib::ustring("<node name=\"mynode\" test=\"myPattern\" />"));

    list<XmlParameter>::iterator it = xmlNode->get_parameters().begin();

    //cout << it->get_name() <<  ":" << it->get_value() << std::endl;

    while(it != xmlNode->get_parameters().end())
    {
        std::cout << it->get_name() << std::endl; // << ": " << it->get_value() << std::endl;
        it++;
    }

    std::cin >> in;
}
