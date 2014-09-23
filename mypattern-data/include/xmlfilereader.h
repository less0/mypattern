#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <filereader.h>
#include <glibmm/ustring.h>
#include <xmlnode.h>
#include <memory>


namespace MyPattern
{
    namespace Data
    {
        class XmlFileReader : public FileReader
        {
            public:
                XmlFileReader();

                void read(Glib::ustring filename);
                shared_ptr<XmlNode> get_root_node();
            protected:
            private:
                /** \brief Reads all data from a file
                *
                */
                Glib::ustring read_file(Glib::ustring filename);
                /** \brief Converts a PartDefinition serialized to XML back to
                * its object representation
                */

                Glib::ustring m_raw_xml;
                shared_ptr<XmlNode> m_root_node;
        };
    }
}

#endif // XMLFILEREADER_H
