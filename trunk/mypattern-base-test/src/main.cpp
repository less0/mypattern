#include <iostream>
#include <limits>

#include <landmark.h>

//#include "xmlnode.h"

//void node_out(shared_ptr<XmlNode>, int);
using namespace MyPattern::Base;

int main()
{
    Landmark* l= new Landmark();
    l->set_definition_x("$ad.X*#test*$bd.X");
    l->set_definition_y("$bd.Y*#blabla");
    list<Glib::ustring> dependencies = l->depends_on();

    for(list<Glib::ustring>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
    {
        std::cout << *it << std::endl;
    }



//    Glib::ustring in;
//    shared_ptr<XmlNode> xmlNode = XmlNode::parse(Glib::ustring("<node name=\"mynode\" test=\"myPattern\"><subnode name=\"asubnode\" /></node>"));
//
//    node_out(xmlNode, 0);
//
////    list<XmlParameter> listOfParameters = xmlNode->get_parameters();
////    list<XmlParameter>::iterator it = listOfParameters.begin();
////
////    //cout << it->get_name() <<  ":" << it->get_value() << std::endl;
////
////    while(it != listOfParameters.end())
////    {
////        std::cout << it->get_name() << ": " << it->get_value() << std::endl;
////        it++;
////    }
//
//    delete l;

     std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
}

//void node_out(shared_ptr<XmlNode> node, int level)
//{
//    Glib::ustring indent = "";
//
//    for(int i=0; i<level; i++)
//    {
//        indent += "\t";
//    }
//
//    std::cout << indent << node->get_name() << std::endl;
//
//    list<XmlParameter> listOfParameters = node->get_parameters();
//    list<XmlParameter>::iterator it_parameters = listOfParameters.begin();
//
//    while(it_parameters != listOfParameters.end())
//    {
//        std::cout
//            << indent
//            << "\t"
//            << it_parameters->get_name()
//            << ": "
//            << it_parameters->get_value()
//            << std::endl;
//
//        it_parameters++;
//    }
//
//    list<shared_ptr<XmlNode>> listOfNodes = node->get_nodes();
//    list<shared_ptr<XmlNode>>::iterator it_node = listOfNodes.begin();
//
//    while(it_node != listOfNodes.end())
//    {
//        node_out(*it_node, level + 1);
//        it_node++;
//    }
//}
