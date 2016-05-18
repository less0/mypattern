#include "mypattern-base.h"
#include "measures.h"
#include "UnitTest++.h"

#include <iostream>

using namespace MyPattern::Data;
using namespace std;

namespace PartDefintionIntegration
{
struct PartDefinitionFixture
{
    PartDefinitionFixture() : _partDefinition()
    {}

    PartDefinition _partDefinition;
};

bool name_change_request_handler(string name)
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

    list<string> landmark_names;
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
    _partDefinition.signal_name_change_request().connect(ptr_fun1<string,bool>(&name_change_request_handler));
    _partDefinition.set_name("Test3141");
    CHECK_EQUAL("Test3141", _partDefinition.get_name());
}


TEST_FIXTURE(PartDefinitionFixture, ChangeNameFail)
{
    _partDefinition.signal_name_change_request().connect(ptr_fun1<string,bool>(&name_change_request_handler));
    _partDefinition.set_name("Test1");
    _partDefinition.set_name("Reserved");
    CHECK_EQUAL("Test1", _partDefinition.get_name());
}

TEST(ParseFromXml)
{
	shared_ptr<BezierDefinition> bezierPrototype = shared_ptr<BezierDefinition>(new BezierDefinition());
	CurveDefinition::register_class(bezierPrototype);
	
    shared_ptr<XmlNode> partDefinitionNode = shared_ptr<XmlNode>(new XmlNode("part"));
    partDefinitionNode->add_attribute(XmlAttribute("name", "part1"));

    shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm1"));
    landmarkNode->add_attribute(XmlAttribute("x", "0"));
    landmarkNode->add_attribute(XmlAttribute("y", "0"));
    partDefinitionNode->add_node(landmarkNode);

    landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm2"));
    landmarkNode->add_attribute(XmlAttribute("x", "#mv1"));
    landmarkNode->add_attribute(XmlAttribute("y", "0"));
    partDefinitionNode->add_node(landmarkNode);

    landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm3"));
    landmarkNode->add_attribute(XmlAttribute("x", "0"));
    landmarkNode->add_attribute(XmlAttribute("y", "#mv1"));
    partDefinitionNode->add_node(landmarkNode);

    landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm4"));
    landmarkNode->add_attribute(XmlAttribute("x", "#mv1"));
    landmarkNode->add_attribute(XmlAttribute("y", "#mv1"));
    partDefinitionNode->add_node(landmarkNode);

    shared_ptr<XmlNode> curve_node = shared_ptr<XmlNode>(new XmlNode("curve"));
    curve_node->add_attribute(XmlAttribute("name", "c1"));
    curve_node->add_attribute(XmlAttribute("type", "bezier"));
	
	list<string> landmark_references;
	landmark_references.push_back("lm1");
	landmark_references.push_back("lm2");
	landmark_references.push_back("lm3");
	landmark_references.push_back("lm4");
	
	for(list<string>::iterator it = landmark_references.begin();
		it != landmark_references.end();
		it++)
	{
		shared_ptr<XmlNode> lmref = shared_ptr<XmlNode>(new XmlNode("lmref"));
		lmref->set_text(*it);
		curve_node->add_node(lmref);
	}
		
	partDefinitionNode->add_node(curve_node);

    shared_ptr<Measures> measures = shared_ptr<Measures>(new Measures());
    measures->define("mv1", "test", 1.0);

    shared_ptr<PartDefinition> parsedPartDefiniton = PartDefinition::deserialize_from_xml(partDefinitionNode, measures);
	CHECK_EQUAL(false, parsedPartDefiniton == NULL);
	CHECK_EQUAL("part1", parsedPartDefiniton->get_name());
	
	list<shared_ptr<Landmark>> landmarks = parsedPartDefiniton->get_landmarks();
	CHECK_EQUAL(4, landmarks.size());
	
	list<shared_ptr<Landmark>>::iterator it = landmarks.begin();
	CHECK_EQUAL("lm1", (*it)->get_name());
	CHECK_EQUAL("0", (*it)->get_definition_x());
	
	it++;
	CHECK_EQUAL("lm2", (*it)->get_name());
	CHECK_EQUAL("#mv1", (*it)->get_definition_x());
	CHECK_EQUAL("0", (*it)->get_definition_y());
	
	list<shared_ptr<CurveDefinition>> curveDefinitions = parsedPartDefiniton->get_curve_definitions();
	CHECK_EQUAL(1, curveDefinitions.size());
	list<shared_ptr<CurveDefinition>>::iterator it_curve = curveDefinitions.begin();
	CHECK_EQUAL(false, *it_curve == NULL);
	CHECK_EQUAL("c1", (*it_curve)->get_name());
	list<string> lmrefs = (*it_curve)->get_landmarks();
	CHECK_EQUAL(4, lmrefs.size());
	list<string>::iterator it_lmrefs = lmrefs.begin();
	CHECK_EQUAL("lm1", *it_lmrefs++);
	CHECK_EQUAL("lm2", *it_lmrefs++);
	CHECK_EQUAL("lm3", *it_lmrefs++);
	CHECK_EQUAL("lm4", *it_lmrefs);
	
	Part evaluatedPart = parsedPartDefiniton->get_part();
	list<Point> points = evaluatedPart.get_points();
	list<Point>::iterator it_points = points.begin();
	CHECK_EQUAL(0, it_points->get_x());
	CHECK_EQUAL(0, it_points->get_y());
	CHECK_EQUAL("lm1", it_points->get_landmark_name());
	it_points++;
	CHECK_EQUAL(1, it_points->get_x());
	CHECK_EQUAL(0, it_points->get_y());
	CHECK_EQUAL("lm2", it_points->get_landmark_name());
	it_points++;
	CHECK_EQUAL(0, it_points->get_x());
	CHECK_EQUAL(1, it_points->get_y());
	CHECK_EQUAL("lm3", it_points->get_landmark_name());
	it_points++;
	CHECK_EQUAL(1, it_points->get_x());
	CHECK_EQUAL(1, it_points->get_y());
	CHECK_EQUAL("lm4", it_points->get_landmark_name());
	
	list<BezierComplex> curves = evaluatedPart.get_curves();
	CHECK_EQUAL(1, curves.size());
	list<BezierComplex>::iterator it_evaluatedCurves = curves.begin();
	
	CHECK_CLOSE(.0, it_evaluatedCurves->get_coordinate(0).get_x(), 1e-6);
	CHECK_CLOSE(.0, it_evaluatedCurves->get_coordinate(0).get_y(), 1e-6);
	
	CHECK_EQUAL(true, it_evaluatedCurves->get_coordinate(.25).get_x() > it_evaluatedCurves->get_coordinate(.25).get_y());
	
	CHECK_CLOSE(.5, it_evaluatedCurves->get_coordinate(.5).get_x(), 1e-6);
	CHECK_CLOSE(.5, it_evaluatedCurves->get_coordinate(.5).get_y(), 1e-6);
	
	CHECK_EQUAL(true, it_evaluatedCurves->get_coordinate(.75).get_x() < it_evaluatedCurves->get_coordinate(.75).get_y());
	
	for(int i=0; i<=10; i++)
	{
		std::cout << "X=" << it_evaluatedCurves->get_coordinate(double(i) / 10.0).get_x() << std::endl;
		std::cout << "Y=" << it_evaluatedCurves->get_coordinate(double(i) / 10.0).get_y() << std::endl;
		std::cout << std::endl;
	}
}

TEST(ParseInvalidNodeException)
{
    shared_ptr<XmlNode> partDefinitionNode = shared_ptr<XmlNode>(new XmlNode("part"));
    partDefinitionNode->add_attribute(XmlAttribute("name", "part1"));

    shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmurks"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm1"));
    landmarkNode->add_attribute(XmlAttribute("x", "0"));
    landmarkNode->add_attribute(XmlAttribute("y", "0"));
    partDefinitionNode->add_node(landmarkNode);

    shared_ptr<Measures> measures = shared_ptr<Measures>(new Measures());
    measures->define("mv1", "test", 1.0);

	CHECK_THROW(PartDefinition::deserialize_from_xml(partDefinitionNode, measures), ArgumentException);
}

TEST(ParseNameMissingException)
{
    shared_ptr<XmlNode> partDefinitionNode = shared_ptr<XmlNode>(new XmlNode("part"));

    shared_ptr<XmlNode> landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm1"));
    landmarkNode->add_attribute(XmlAttribute("x", "0"));
    landmarkNode->add_attribute(XmlAttribute("y", "0"));
    partDefinitionNode->add_node(landmarkNode);

    landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm2"));
    landmarkNode->add_attribute(XmlAttribute("x", "#mv1"));
    landmarkNode->add_attribute(XmlAttribute("y", "0"));
    partDefinitionNode->add_node(landmarkNode);

    landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm3"));
    landmarkNode->add_attribute(XmlAttribute("x", "#mv1"));
    landmarkNode->add_attribute(XmlAttribute("y", "#mv1"));
    partDefinitionNode->add_node(landmarkNode);

    landmarkNode = shared_ptr<XmlNode>(new XmlNode("landmark"));
    landmarkNode->add_attribute(XmlAttribute("name", "lm4"));
    landmarkNode->add_attribute(XmlAttribute("x", "0"));
    landmarkNode->add_attribute(XmlAttribute("y", "#mv1"));
    partDefinitionNode->add_node(landmarkNode);

    shared_ptr<XmlNode> curve_node = shared_ptr<XmlNode>(new XmlNode("curve"));
    curve_node->add_attribute(XmlAttribute("name", "c1"));
    curve_node->add_attribute(XmlAttribute("type", "bezier"));
    shared_ptr<XmlNode> lmref1 = shared_ptr<XmlNode>(new XmlNode("lmref"));

    shared_ptr<Measures> measures = shared_ptr<Measures>(new Measures());
    measures->define("mv1", "test", 1.0);

    CHECK_THROW(PartDefinition::deserialize_from_xml(partDefinitionNode, measures), ArgumentException);
}
}
