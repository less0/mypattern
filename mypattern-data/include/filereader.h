#ifndef FILEREADER_H
#define FILEREADER_H

#include <glibmm/ustring.h>
#include <mypattern-base.h>
#include <memory>

namespace MyPattern
{
    namespace Data
    {
        /*! \brief Abstract base class to provide an interface to read patterns
         * from files.
         */
        class FileReader
        {
            public:
                /*! \brief Reads a pattern from a file
                 *
                 * This method reads a pattern definition from a file and returns it.
                 */
                virtual shared_ptr<MyPattern::Base::PatternDefinition> read_pattern(Glib::ustring) = 0;

                /*! \brief Reads personal measures from a file
                 *
                 * This function reads a measures file. The measures file is parsed with default
                 * values and  - if read_personal_value is true - also with personalized measures.
                 * The latter case is intended to be used to load the actual measures of a peprson
                 * the former to read and write default measures.
                 */
                virtual shared_ptr<MyPattern::Base::Measures> read_measures(Glib::ustring,bool) = 0;
            protected:
            private:
        };
    }
}

#endif // FILEREADER_H
