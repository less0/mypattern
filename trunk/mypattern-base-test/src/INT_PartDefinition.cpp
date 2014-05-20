#include "mypattern-base.h"
#include "UnitTest++.h"


namespace PartDefintionIntegration
{
    struct PartDefinitionFixture
    {
        PartDefinitionFixture() : _partDefinition()
        {}

        PartDefinition _partDefinition;
    };

    TEST_FIXTURE(PartDefinitionFixture, AddLandmarks)
    {
        shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
        lm1->set_name("lm1");
        lm1->set_definition_x("1.0");
        lm1->set_definition_y("1.0");

        CHECK_EQUAL(true, _partDefinition.add_landmark(lm1));

        shared_ptr<Landmark> lm1_retrieved = _partDefinition.get_landmark("lm1");

        CHECK_EQUAL(lm1, lm1_retrieved);
    }

    TEST_FIXTURE(PartDefinitionFixture, EvaluateSingleLandmark)
    {
        shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
        lm1->set_name("lm1");
        lm1->set_definition_x("20.011988");
        lm1->set_definition_y("6.041985");

        _partDefinition.add_landmark(lm1);

        Part evaluatedPart = _partDefinition.get_part();

        list<Point> points = evaluatedPart.get_points();

        CHECK_EQUAL(1, points.size());

        list<Point>::iterator it = points.begin();

        CHECK_EQUAL(20.011988, (*it).get_x());
        CHECK_EQUAL(6.041985, (*it).get_y());
    }

    TEST_FIXTURE(PartDefinitionFixture, EvaluateDependentLandmarks)
    {
        shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
        lm1->set_name("lm1");
        lm1->set_definition_x("1.0");
        lm1->set_definition_y("2.0");

        shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
        lm2->set_name("lm2");
        lm2->set_definition_x("@lm1[Y]+1.0");
        lm2->set_definition_y("@lm1[X]+3.14159");

        _partDefinition.add_landmark(lm1);
        _partDefinition.add_landmark(lm2);

        Part evaluatedPart = _partDefinition.get_part();
        list<Point> points = evaluatedPart.get_points();

        CHECK_EQUAL(2, points.size());

        list<Point>::iterator it = points.begin();
        it++;

        CHECK_EQUAL(2.0+1.0, (*it).get_x());
        CHECK_EQUAL(1.0+3.14159, (*it).get_y());
    }
}
