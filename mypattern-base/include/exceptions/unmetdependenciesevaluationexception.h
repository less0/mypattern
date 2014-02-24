#ifndef MYPATTERN_EXCEPTIONS_UNMETDEPENDENCIESEVALUATIONEXCEPTION_H
#define MYPATTERN_EXCEPTIONS_UNMETDEPENDENCIESEVALUATIONEXCEPTION_H

#include <exceptions/evaluationexception.h>
#include <list>

using namespace std;

namespace MyPattern {
namespace Exceptions {

/*! \brief Exception that is thrown when the EvaluationRoot is unable
* to resolve the dependencies of an object, either when it's added or
* when it's modified.
*/
class UnmetDependenciesEvaluationException : public MyPattern::Exceptions::EvaluationException
{
    public:
        /*! \brief Default constructor with no information specific to the
         * unmet deps
         */
        UnmetDependenciesEvaluationException();

        /*! \brief Constructor that takes a list of unmet dependencies
         */
        UnmetDependenciesEvaluationException(list<ustring> dependencies);
        /** Default destructor */
        virtual ~UnmetDependenciesEvaluationException();
        /** Copy constructor
         *  \param other Object to copy from
         */
        UnmetDependenciesEvaluationException(const UnmetDependenciesEvaluationException& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        UnmetDependenciesEvaluationException& operator=(const UnmetDependenciesEvaluationException& other);

        /*! \brief Gets a list of the names of the unmet dependencies (if
         * available)
         */
        list<ustring> get_unmet_dependencies();
    protected:
    private:
        list<ustring> m_unmet_dependencies;
};

} // namespace Exceptions
} // namespace MyPattern

#endif // MYPATTERN_EXCEPTIONS_UNMETDEPENDENCIESEVALUATIONEXCEPTION_H
