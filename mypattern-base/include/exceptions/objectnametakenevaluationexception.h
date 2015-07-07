#ifndef MYPATTERN_BASE_EXCEPTIONS_OBJECTNAMETAKENEVALUATIONEXCEPTION_H
#define MYPATTERN_BASE_EXCEPTIONS_OBJECTNAMETAKENEVALUATIONEXCEPTION_H

#include <exceptions/evaluationexception.h>

namespace MyPattern {
namespace Exceptions {

class ObjectNameTakenEvaluationException : public MyPattern::Exceptions::EvaluationException
{
    public:
        /** Default constructor */
        ObjectNameTakenEvaluationException(ustring object_name);
        /** Default destructor */
        virtual ~ObjectNameTakenEvaluationException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        ObjectNameTakenEvaluationException(const ObjectNameTakenEvaluationException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        ObjectNameTakenEvaluationException& operator=(const ObjectNameTakenEvaluationException& other);
    protected:
    private:
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_BASE_EXCEPTIONS_OBJECTNAMETAKENEVALUATIONEXCEPTION_H
