#include <iostream>
#include <limits>

#include "xmlnode.h"

int main()
{
    Glib::ustring in;
    shared_ptr<XmlNode> xmlNode = XmlNode::parse(Glib::ustring("<node name=\"mynode\" test=\"myPattern\" />"));

    list<XmlParameter> listOfParameters = xmlNode->get_parameters();
    list<XmlParameter>::iterator it = listOfParameters.begin();

    //cout << it->get_name() <<  ":" << it->get_value() << std::endl;

    while(it != listOfParameters.end())
    {
        std::cout << it->get_name() << ": " << it->get_value() << std::endl;
        it++;
    }

     std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
}
