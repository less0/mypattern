#ifndef MYPATTERN_BASE_EXCEPTIONS_FORMULAEVALUATIONEXCEPTION_H
#define MYPATTERN_BASE_EXCEPTIONS_FORMULAEVALUATIONEXCEPTION_H

#include <exception.h>
#include <string>

using namespace std;

namespace MyPattern {
namespace Exceptions {

class FormulaEvaluationException : public Exception
{
    public:
        /** Default constructor */
        FormulaEvaluationException(string message);

        /** Default destructor */
        virtual ~FormulaEvaluationException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        FormulaEvaluationException(const FormulaEvaluationException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        FormulaEvaluationException& operator=(const FormulaEvaluationException& other);
		
		std::string get_type() { return typeid(*this).name(); }

    protected:
    private:
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_BASE_EXCEPTIONS_FORMULAEVALUATIONEXCEPTION_H
