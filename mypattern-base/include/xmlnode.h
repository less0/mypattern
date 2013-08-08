#ifndef XMLNODE_H
#define XMLNODE_H

#include "xmlparameter.h"
#include "glibmm/ustring.h"
#include <list>
#include <memory>
#include <sstream>

using namespace std;

class XmlNode
{
    public:
        XmlNode();
        XmlNode(const XmlNode& base);

        static shared_ptr<XmlNode> parse(Glib::ustring);

        Glib::ustring get_name();
        void set_name(Glib::ustring);

        list<XmlParameter> get_parameters();
        bool add_parameter(XmlParameter);
        bool remove_parameter(XmlParameter);
        bool remove_parameter(Glib::ustring);

        list<shared_ptr<XmlNode>> get_nodes();
        void add_node(shared_ptr<XmlNode>);
        //bool remove_node(shared_ptr<XmlNode>);
    protected:
    private:
        static list<Glib::ustring> split_nodes(Glib::ustring);
        static Glib::ustring get_tag(Glib::ustring schema, int index);
        static int find_end_tag(Glib::ustring schema,Glib::ustring tag_name);
        static bool tag_is_terminated(Glib::ustring tag);

        Glib::ustring m_name;
        list<XmlParameter> m_parameters;
        list<shared_ptr<XmlNode>> m_subnodes;
};

#endif // XMLNODE_H
