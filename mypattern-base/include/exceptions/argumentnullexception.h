#ifndef MYPATTERN_EXCEPTIONS_ARGUMENTNULLEXCEPTION_H
#define MYPATTERN_EXCEPTIONS_ARGUMENTNULLEXCEPTION_H

#include <exception.h>
#include <string>

using namespace std;

namespace MyPattern {
namespace Exceptions {

class ArgumentNullException : public MyPattern::Exceptions::Exception
{
    public:
        /** Default constructor */
        ArgumentNullException(string argument_name);
        /** Default destructor */
        virtual ~ArgumentNullException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ArgumentNullException(const ArgumentNullException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ArgumentNullException& operator=(const ArgumentNullException& other);
    protected:
    private:
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_ARGUMENTNULLEXCEPTION_H
