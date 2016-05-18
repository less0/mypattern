#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
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
               void read(std::string);
            protected:
            private:
        };
    }
}

#endif // FILEREADER_H
