#ifndef MYPATTERN_EXCEPTIONS_CIRCULARDEPENDENCYEVALUATIONEXCEPTION_H
#define MYPATTERN_EXCEPTIONS_CIRCULARDEPENDENCYEVALUATIONEXCEPTION_H

#include <exceptions/evaluationexception.h>

namespace MyPattern {
namespace Exceptions {

class CircularDependencyEvaluationException : public MyPattern::Exceptions::EvaluationException
{
    public:
        /** Default constructor */
        CircularDependencyEvaluationException();
        /** Default destructor */
        virtual ~CircularDependencyEvaluationException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        CircularDependencyEvaluationException(const CircularDependencyEvaluationException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        CircularDependencyEvaluationException& operator=(const CircularDependencyEvaluationException& other);
    protected:
    private:
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_CIRCULARDEPENDENCYEVALUATIONEXCEPTION_H
