#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <filereader.h>
#include <string>
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

                void read(std::string filename);
                shared_ptr<XmlNode> get_root_node();
            protected:
            private:
                /** \brief Reads all data from a file
                *
                */
                std::string read_file(std::string filename);
                /** \brief Converts a PartDefinition serialized to XML back to
                * its object representation
                */

                std::string m_raw_xml;
                shared_ptr<XmlNode> m_root_node;
        };
    }
}

#endif // XMLFILEREADER_H
