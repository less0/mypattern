#ifndef XMLNODE_H
#define XMLNODE_H

#include "xmlattribute.h"
#include "xmlelement.h"
#include <string>
#include <list>
#include <memory>
#include <sstream>

using namespace std;
using namespace Glib;

namespace MyPattern
{
    namespace Data
    {
        /*! \brief Class representing nodes in an XML-Tree.
        *
        * This class provides the functionality to parse nodes from an XML tree and
        * represent them hierarchically. Besides subnodes, nodes may contain parameters
        * represented by objects of the XmlAttribute class.
        */
        class XmlNode
        {
            public:
                XmlNode();

                XmlNode(std::string name);
                /*! \brief Creates a deep copy of an existing XmlNode.
                */
                XmlNode(const XmlNode& base);

                /*! \brief Gets the name of the XmlNode
                */
                std::string get_name();
                /*! \brief Sets the name of the XmlNode
                */
                void set_name(std::string);

                /*! \brief Gets a list of all parameters of the current node
                */
                list<XmlAttribute> get_attributes();
                /*! \brief Adds a new parameter to the XmlNode
                */
                bool add_attribute(XmlAttribute);

                bool remove_attribute(XmlAttribute);
                bool remove_attribute(std::string);

                /*! \brief Gets a list of all subnodes */
                list<shared_ptr<XmlNode>> get_nodes();
                /*! \brief Adds a new subnode */
                void add_node(shared_ptr<XmlNode>);

                bool is_text_node();
                std::string get_text();
                void set_text(std::string);


                /*! \brief Parses an XmlNode from text
                *
                * This function is meant to be used on a single node, or the root of the
                * XML-Document. An XML-Document may not contain more than one node on
                * root level, thus returning one document ist sufficient.
                * Anyway, doctype and other tags are not parsed ATM, thus embedding the
                * root node in some form of XmlDocument type may be sensible
                */
                static shared_ptr<XmlNode> parse(std::string);
            protected:
            private:
                static list<std::string> split_nodes(std::string);
                /*! \brief Gets a list of subnodes of the current node
                *
                * It turned out, that the split_nodes function was not
                * sufficient to parse complex XML-statements, thus, a new
                * recursive parsing approach is implemented, that reads and
                * parses the nodes all at once.
                */
                static list<shared_ptr<XmlNode>> parse_subnodes(std::string schema, std::string parentNodeName, int start_index, int& end_index, std::string& text);
				static shared_ptr<XmlNode> parse_node(std::string schema, int start_index, int& end_index);
                static shared_ptr<XmlElement> parse_element(std::string schema, int start_index);
                static std::string get_tag(std::string schema, int index);
                static int find_end_tag(std::string schema,std::string tag_name);
                static bool tag_is_terminated(std::string tag);

                std::string m_name;
                std::string m_text;
                list<XmlAttribute> m_parameters;
                list<shared_ptr<XmlNode>> m_subnodes;
        };
    }
}

#endif // XMLNODE_H
