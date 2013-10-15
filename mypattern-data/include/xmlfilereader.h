#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <filereader.h>
#include <glibmm/ustring.h>
#include <patterndefinition.h>
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
                /**\brief Reads a pattern from a file specified with
                * set_filename
                *
                * When a filename has been specified before, this function opens
                * the specified file, reads the XML-Tree and converts it to a
                * pattern
                */
                shared_ptr<PatternDefinition> read_pattern();
                /**\brief Sets the name of the file to open
                *
                */
                void set_filename(Glib::ustring filename);
                /**\brief Gets the file specified with set_filename
                *
                */
                Glib::ustring get_filename();

            protected:
            private:
                /** \brief Reads all data from a file
                *
                */
                Glib::ustring read_file(Glib::ustring filename);
                /** \brief Converts a PartDefinition serialized to XML back to
                * its object representation
                */
                shared_ptr<PartDefinition> get_part(shared_ptr<XmlNode>,
                    shared_ptr<PatternDefinition>);
                /** \brief Convers a Landmark serialized to XML back to its
                * object representation.
                */
                shared_ptr<Landmark> get_landmark(shared_ptr<XmlNode>,
                    shared_ptr<PartDefinition>);
                /** \brief Converts a CurveDefinition serialized to XML back to
                * its object representation
                */
                shared_ptr<CurveDefinition> get_curve(shared_ptr<XmlNode>,
                    shared_ptr<PartDefinition>);
                /** \brief Converts a PatternParameter serialized to XML back to
                * its object representation
                */
                shared_ptr<PatternParameter> get_parameter(shared_ptr<XmlNode>,
                    shared_ptr<PatternDefinition>);


                Glib::ustring m_filename;
        };
    }
}

#endif // XMLFILEREADER_H
