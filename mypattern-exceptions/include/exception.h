#ifndef MYPATTERN_EXCEPTIONS_EXCEPTION_H
#define MYPATTERN_EXCEPTIONS_EXCEPTION_H

#include <string>
#include <typeinfo>

namespace MyPattern {
namespace Exceptions {

class Exception
{
    public:
        /** Default constructor */
        Exception() {}
        /*! Constructor with a custom message */
        Exception(std::string);
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
        std::string get_message() { return m_message; }
        /** Access m_stacktrace
         * \return The current value of m_stacktrace
         */
        std::string get_stacktrace() { return m_stacktrace; }
		
		virtual std::string get_type() { return typeid(this).name(); }
    protected:
        std::string m_message; //!< Member variable "m_message"
    private:
        std::string m_stacktrace; //!< Member variable "m_stacktrace"
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_EXCEPTION_H
