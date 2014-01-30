#ifndef XMLNODE_H
#define XMLNODE_H

#include "xmlattribute.h"
#include "xmlelement.h"
#include "glibmm/ustring.h"
#include <list>
#include <memory>
#include <sstream>

using namespace std;

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

                XmlNode(Glib::ustring name);
                /*! \brief Creates a deep copy of an existing XmlNode.
                */
                XmlNode(const XmlNode& base);

                /*! \brief Gets the name of the XmlNode
                */
                Glib::ustring get_name();
                /*! \brief Sets the name of the XmlNode
                */
                void set_name(Glib::ustring);

                /*! \brief Gets a list of all parameters of the current node
                */
                list<XmlAttribute> get_parameters();
                /*! \brief Adds a new parameter to the XmlNode
                */
                bool add_parameter(XmlAttribute);

                bool remove_parameter(XmlAttribute);
                bool remove_parameter(Glib::ustring);

                /*! \brief Gets a list of all subnodes */
                list<shared_ptr<XmlNode>> get_nodes();
                /*! \brief Adds a new subnode */
                void add_node(shared_ptr<XmlNode>);

                /*! \brief Parses an XmlNode from text
                *
                * This function is meant to be used on a single node, or the root of the
                * XML-Document. An XML-Document may not contain more than one node on
                * root level, thus returning one document ist sufficient.
                * Anyway, doctype and other tags are not parsed ATM, thus embedding the
                * root node in some form of XmlDocument type may be sensible
                */
                static shared_ptr<XmlNode> parse(Glib::ustring);
            protected:
            private:
                static list<Glib::ustring> split_nodes(Glib::ustring);
                /*! \brief Gets a list of subnodes of the current node
                *
                * It turned out, that the split_nodes function was not
                * sufficient to parse complex XML-statements, thus, a new
                * recursive parsing approach is implemented, that reads and
                * parses the nodes all at once.
                */
                static list<shared_ptr<XmlNode>> parse_subnodes(Glib::ustring schema, Glib::ustring parentNodeName, int start_index, int& end_index);
                static shared_ptr<XmlElement> parse_element(Glib::ustring schema, int start_index);
                static Glib::ustring get_tag(Glib::ustring schema, int index);
                static int find_end_tag(Glib::ustring schema,Glib::ustring tag_name);
                static bool tag_is_terminated(Glib::ustring tag);

                Glib::ustring m_name;
                list<XmlAttribute> m_parameters;
                list<shared_ptr<XmlNode>> m_subnodes;
        };
    }
}

#endif // XMLNODE_H
