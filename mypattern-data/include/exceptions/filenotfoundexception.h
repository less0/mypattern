#ifndef MYPATTERN_DATA_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H
#define MYPATTERN_DATA_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H

#include <exception.h>

namespace MyPattern {
namespace Data {
namespace Exceptions {

class FileNotFoundException : public MyPattern::Exceptions::Exception
{
    public:
        FileNotFoundException();
        virtual ~FileNotFoundException();
    protected:
    private:
};

} // namespace Exceptions
} // namespace Data
} // namespace MyPattern

#endif // MYPATTERN_DATA_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H