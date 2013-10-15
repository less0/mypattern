#ifndef FILEREADER_H
#define FILEREADER_H

#include <glibmm/ustring.h>
#include <patterndefinition.h>
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
//                virtual FileReader(Glib::ustring fileName);
                virtual shared_ptr<PatternDefinition> read_pattern() = 0;
                virtual void set_filename(Glib::ustring filename) = 0;
                virtual Glib::ustring get_filename();
            protected:
            private:
        };
    }
}

#endif // FILEREADER_H
