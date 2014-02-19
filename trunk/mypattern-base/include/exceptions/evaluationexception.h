#ifndef MYPATTERN_EXCEPTIONS_EVALUATIONEXCEPTION_H
#define MYPATTERN_EXCEPTIONS_EVALUATIONEXCEPTION_H

#include <exceptions/exception.h>

namespace MyPattern {
namespace Exceptions {

class EvaluationException : public MyPattern::Exceptions::Exception
{
    public:
        /** Default constructor */
        EvaluationException();
        /** Default destructor */
        virtual ~EvaluationException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        EvaluationException(const EvaluationException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        EvaluationException& operator=(const EvaluationException& other);
    protected:
    private:
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_EVALUATIONEXCEPTION_H
