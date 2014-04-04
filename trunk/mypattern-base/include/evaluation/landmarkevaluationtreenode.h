#ifndef MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H
#define MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H

#include <evaluation/evaluationtreenode.h>
#include <landmark.h>
#include <sigc++/sigc++.h>
#include <point.h>

namespace MyPattern {
namespace Base {
namespace Evaluation {

class LandmarkEvaluationTreeNode : public MyPattern::Base::Evaluation::EvaluationTreeNode
{
    public:
        /** Default constructor */
        LandmarkEvaluationTreeNode();

        LandmarkEvaluationTreeNode(shared_ptr<Landmark> landmark);

        ~LandmarkEvaluationTreeNode()
        {}

        void notify_update();

        list<ustring> depends_on() { return m_base_landmark->depends_on(); }

        shared_ptr<Landmark> get_landmark()
        {
            return m_base_landmark;
        }

        ustring get_prefixed_name();

        /*! \brief Gets the last value of the associated landmark given the values of the
         * dependencies
         */
        Point get_value();

	/*! \brief Gets the signal that checks the validity of a dependency
         * change */
        sigc::signal2<bool, shared_ptr<EvaluationTreeNode>, list<ustring>> signal_request_change;

        /*! \brief Returns the signal that is emitted when the object has been
         * updated and the dependencies are to be updated by the EvaluationRoot */
        sigc::signal1<void, shared_ptr<EvaluationTreeNode>> signal_update_dependencies;
    protected:
    private:
        shared_ptr<Landmark> m_base_landmark;
        Point m_cached_value;

        /*! \brief Signal handler for Landmark::signal_request_change */
        bool base_landmark_change_request(list<ustring> new_dependencies);

        /*! \brief Signal handler for Landmark::signal_change */
        void base_landmark_changed();

        /*! \brief Recalculates the value of the associated Landmark given the values of the
         * dependencies.
         *
         * \see get_value
         */
        void update_value();
};

} // namespace Evaluation
} // namespace Base
} // namespace MyPattern

#endif // MYPATTERN_BASE_EVALUATION_LANDMARKEVALUATIONTREENODE_H
