#ifndef MYPATTERN_BASE_EVALUATION_EVALUATIONTREEOBSERVER_H
#define MYPATTERN_BASE_EVALUATION_EVALUATIONTREEOBSERVER_H

namespace MyPattern {
namespace Base {
namespace Evaluation {

class EvaluationTreeObserver
{
    public:
        virtual void notify_update() = 0;
    protected:
    private:
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_EVALUATIONTREEOBSERVER_H
