#ifndef MYPATTERN_EXCEPTIONS_EXCEPTION_H
#define MYPATTERN_EXCEPTIONS_EXCEPTION_H

#include "glibmm/ustring.h"

using namespace Glib;

namespace MyPattern {
namespace Exceptions {

class Exception
{
    public:
        /** Default constructor */
        Exception() {}
        /*! Constructor with a custom message */
        Exception(Glib::ustring);
        /** Default destructor */
        virtual ~Exception() {}
        /** Copy constructor
         *  \param other Object to copy from
         */
        Exception(const Exception& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Exception& operator=(const Exception& other);
        /** Access m_message
         * \return The current value of m_message
         */
        ustring get_message() { return m_message; }
        /** Access m_stacktrace
         * \return The current value of m_stacktrace
         */
        ustring get_stacktrace() { return m_stacktrace; }
		
		ustring get_type() { return "Exception"; }
    protected:
        ustring m_message; //!< Member variable "m_message"
    private:
        ustring m_stacktrace; //!< Member variable "m_stacktrace"
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_EXCEPTION_H
