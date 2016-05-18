#ifndef MYPATTERN_EXCEPTIONS_ARGUMENTEXCEPTION_H
#define MYPATTERN_EXCEPTIONS_ARGUMENTEXCEPTION_H

#include <exception.h>
#include <string>

using namespace std;

namespace MyPattern {
namespace Exceptions {

class ArgumentException : public MyPattern::Exceptions::Exception
{
    public:
        /** Default constructor */
        ArgumentException(string argument_name);
        /** Default destructor */
        virtual ~ArgumentException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ArgumentException(const ArgumentException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ArgumentException& operator=(const ArgumentException& other);
    protected:
    private:
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_ARGUMENTEXCEPTION_H
