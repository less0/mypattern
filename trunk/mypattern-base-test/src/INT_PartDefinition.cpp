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

bool name_change_request_handler(Glib::ustring name)
{
    if(name == "Reserved")
    {
        return false;
    }

    return true;
}

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

TEST_FIXTURE(PartDefinitionFixture, EvaluateCurve)
{
    shared_ptr<Landmark> lm1 = shared_ptr<Landmark>(new Landmark());
    lm1->set_name("lm1");
    lm1->set_definition_x("0.0");
    lm1->set_definition_y("0.0");


    shared_ptr<Landmark> lm2 = shared_ptr<Landmark>(new Landmark());
    lm2->set_name("lm2");
    lm2->set_definition_x("0.5");
    lm2->set_definition_y("0.0");

    shared_ptr<Landmark> lm3 = shared_ptr<Landmark>(new Landmark());
    lm3->set_name("lm3");
    lm3->set_definition_x("0.5");
    lm3->set_definition_y("1.0");

    shared_ptr<Landmark> lm4 = shared_ptr<Landmark>(new Landmark());
    lm4->set_name("lm4");
    lm4->set_definition_x("1.0");
    lm4->set_definition_y("1.0");

    shared_ptr<CurveDefinition> bezier = dynamic_pointer_cast<CurveDefinition>(shared_ptr<BezierDefinition>(new BezierDefinition()));

    list<Glib::ustring> landmark_names;
    landmark_names.push_back("lm1");
    landmark_names.push_back("lm2");
    landmark_names.push_back("lm3");
    landmark_names.push_back("lm4");
    bezier->set_landmarks(landmark_names);

    _partDefinition.add_landmark(lm1);
    _partDefinition.add_landmark(lm2);
    _partDefinition.add_landmark(lm3);
    _partDefinition.add_landmark(lm4);
    _partDefinition.add_curve_definition(bezier);

    Part evaluated_part = _partDefinition.get_part();
    list<BezierComplex> curves = evaluated_part.get_curves();

    CHECK_EQUAL(1, curves.size());

    list<BezierComplex>::iterator it = curves.begin();
    Point p = it->get_coordinate(0.0);

    CHECK_CLOSE(.0, p.get_x(), 1e-9);
    CHECK_CLOSE(.0, p.get_y(), 1e-9);

    p = it->get_coordinate(.5);

    CHECK_CLOSE(.5, p.get_x(), 1e-9);
    CHECK_CLOSE(.5, p.get_y(), 1e-9);

    p = it->get_coordinate(1.0);

    CHECK_CLOSE(1.0, p.get_x(), 1e-9);
    CHECK_CLOSE(1.0, p.get_y(), 1e-9);
}

TEST_FIXTURE(PartDefinitionFixture, AddMeasureValues)
{
    shared_ptr<Measures> measures = shared_ptr<Measures>(new Measures());
    measures->define("mv1", "", 1.0);
    measures->define("mv2", "", 2.0);

    CHECK_EQUAL(true, _partDefinition.set_measures(measures));

    shared_ptr<Measures> measures_out = _partDefinition.get_measures();

    list<shared_ptr<MeasureValue>> measure_values = measures_out->get_measure_values();
    CHECK_EQUAL(2, measure_values.size());
    list<shared_ptr<MeasureValue>>::iterator it = measure_values.begin();
    CHECK_EQUAL("mv1", (*it)->get_name());
    CHECK_EQUAL(1.0, (*it)->get_value());

    it++;

    CHECK_EQUAL("mv2", (*it)->get_name());
    CHECK_EQUAL(2.0, (*it)->get_value());
}

TEST_FIXTURE(PartDefinitionFixture, ReplaceMeasures)
{
    shared_ptr<Measures> measures1 = shared_ptr<Measures>(new Measures());
    measures1->define("mv1", "Erstes Set", 1.0);
    measures1->define("mv2", "Erstes Set", 2.0);

    CHECK_EQUAL(true, _partDefinition.set_measures(measures1));

    shared_ptr<Measures> measures2 = shared_ptr<Measures>(new Measures());
    measures2->define("mv1", "Erstes Set", 1.5);
    measures2->define("mv2", "Erstes Set", 2.5);

    CHECK_EQUAL(true, _partDefinition.set_measures(measures2));

    shared_ptr<Measures> measures_out = _partDefinition.get_measures();

    list<shared_ptr<MeasureValue>> measure_values = measures_out->get_measure_values();
    CHECK_EQUAL(2, measure_values.size());
    list<shared_ptr<MeasureValue>>::iterator it = measure_values.begin();
    CHECK_EQUAL("mv1", (*it)->get_name());
    CHECK_EQUAL(1.5, (*it)->get_value());

    it++;

    CHECK_EQUAL("mv2", (*it)->get_name());
    CHECK_EQUAL(2.5, (*it)->get_value());
}

TEST_FIXTURE(PartDefinitionFixture, EvaluateLandmarkRelativeToMeasureValues)
{
    shared_ptr<Measures> measures = shared_ptr<Measures>(new Measures());
    measures->define("mv1", "Erstes Set", 1.0);
    measures->define("mv2", "Erstes Set", 3.14159);

    CHECK_EQUAL(true, _partDefinition.set_measures(measures));

    shared_ptr<Landmark> landmark = shared_ptr<Landmark>(new Landmark());
    landmark->set_name("lm1");
    landmark->set_definition_x("#mv1");
    landmark->set_definition_y("#mv2*2.0");

    CHECK_EQUAL(true, _partDefinition.add_landmark(landmark));

    Part evaluatedPart = _partDefinition.get_part();
    list<Point> points = evaluatedPart.get_points();

    CHECK_EQUAL(1, points.size());

    list<Point>::iterator it = points.begin();

    CHECK_EQUAL(1.0, (*it).get_x());
    CHECK_EQUAL(2.0*3.14159, (*it).get_y());
}

TEST_FIXTURE(PartDefinitionFixture, ReplaceMeasuresWithDependingLandmarks)
{
}

TEST_FIXTURE(PartDefinitionFixture, TryRemoveMeasuresWithDependingLandmarks)
{
}

TEST_FIXTURE(PartDefinitionFixture, ChangeNameSuccessful)
{
    _partDefinition.signal_name_change_request().connect(ptr_fun1<Glib::ustring,bool>(&name_change_request_handler));
    _partDefinition.set_name("Test3141");
    CHECK_EQUAL("Test3141", _partDefinition.get_name());
}


TEST_FIXTURE(PartDefinitionFixture, ChangeNameFail)
{
    _partDefinition.signal_name_change_request().connect(ptr_fun1<Glib::ustring,bool>(&name_change_request_handler));
    _partDefinition.set_name("Test1");
    _partDefinition.set_name("Reserved");
    CHECK_EQUAL("Test1", _partDefinition.get_name());
}
}
