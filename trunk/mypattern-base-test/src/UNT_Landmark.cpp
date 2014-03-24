#include "UnitTest++.h"
#include "landmark.h"

using namespace MyPattern::Base;

namespace
{
    TEST(SetLandmarkNameTest)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new MyPattern::Base::Landmark());
        landmark->set_name("landmark123");
    }

    TEST(GetLandmarkNameTest)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("LM1");
        CHECK_EQUAL("LM1", landmark->get_name());
    }

    TEST(LandmarkDefaultValuesTest)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        CHECK_EQUAL("0", landmark->get_definition_x());
        CHECK_EQUAL("0", landmark->get_definition_y());
    }

    TEST(LandmarkGetDependencies)
    {
        shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
        landmark->set_name("lm1");
        landmark->set_definition_x("$lm2[X]*2");
        landmark->set_definition_y("$lm2[Y]*2");

        list<ustring> dependencies = landmark->depends_on();

        CHECK_EQUAL(1, dependencies.size());

        list<ustring>::iterator it = dependencies.begin();
        CHECK_EQUAL("$lm2", *it);
    }


}
