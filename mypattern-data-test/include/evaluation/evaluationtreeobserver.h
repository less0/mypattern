#ifndef MYPATTERN_BASE_EVALUATION_EVALUATIONTREEOBSERVER_H
#define MYPATTERN_BASE_EVALUATION_EVALUATIONTREEOBSERVER_H

#include "evaluationtreenode.h"

namespace MyPattern {
namespace Base {
namespace Evaluation {

class EvaluationTreeObserver
{
    public:
        /** Default constructor */
        EvaluationTreeObserver();
        /** Default destructor */
        virtual ~EvaluationTreeObserver();

        notify_update();
    protected:
    private:
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_EVALUATIONTREEOBSERVER_H
