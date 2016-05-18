#include "exceptions/unmetdependenciesevaluationexception.h"

namespace MyPattern {
namespace Exceptions {

UnmetDependenciesEvaluationException::UnmetDependenciesEvaluationException()
{
    //ctor
}

UnmetDependenciesEvaluationException::UnmetDependenciesEvaluationException(list<string> deps)
{
	m_unmet_dependencies = deps;
}


UnmetDependenciesEvaluationException::~UnmetDependenciesEvaluationException()
{
    //dtor
}

UnmetDependenciesEvaluationException::UnmetDependenciesEvaluationException(const UnmetDependenciesEvaluationException& other)
{
    //copy ctor
}

UnmetDependenciesEvaluationException& UnmetDependenciesEvaluationException::operator=(const UnmetDependenciesEvaluationException& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

list<string> UnmetDependenciesEvaluationException::get_unmet_dependencies()
{
    return m_unmet_dependencies;
}

} // namespace Exceptions
} // namespace MyPattern
