#include "UnitTest++.h"
#include "mypattern-base.h"

using namespace MyPattern::Base;

namespace
{
    TEST(TestRegisterClasses)
    {
        shared_ptr<CurveDefinition> bezier_prototype = shared_ptr<CurveDefinition>(new BezierDefinition());

        CurveDefinition::register_class(bezier_prototype);
        list<ustring> class_names = CurveDefinition::get_registered_class_names();
        CHECK_EQUAL(1, class_names.size());
    }


}
