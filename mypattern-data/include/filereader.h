#ifndef FILEREADER_H
#define FILEREADER_H

#include <glibmm/ustring.h>
//#include <mypattern-base.h>
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
               void read(Glib::ustring);
            protected:
            private:
        };
    }
}

#endif // FILEREADER_H
