#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <filereader.h>
#include <glibmm/ustring.h>
#include <patterndefinition.h>
#include <xmlnode.h>
#include <memory>

using namespace MyPattern::Base;

namespace MyPattern
{
    namespace Data
    {
        class XmlFileReader : public FileReader
        {
            public:
                XmlFileReader();

                shared_ptr<PatternDefinition> read_pattern(Glib::ustring);


                shared_ptr<Measures> read_measures(Glib::ustring filename, bool read_personal_values);
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
