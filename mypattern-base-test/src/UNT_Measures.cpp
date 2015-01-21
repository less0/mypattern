#include "UnitTest++.h"
#include "mypattern-base.h"

using namespace MyPattern::Base;

namespace
{
    struct MeasuresFixture
    {

        MeasuresFixture() : _measures()
        {
            _measures.define("mv1", "Messwert1", 1.234);
            _measures.define("mv2", "Messwert2", 3.141);
            _measures.define("mv3", "Messwert3", 2.718);
        }

        Measures _measures;
    };

    TEST_FIXTURE(MeasuresFixture, TestDefinedValues)
    {
        list<shared_ptr<MeasureValue>> values = _measures.get_measure_values();
        CHECK_EQUAL(3, values.size());
        list<shared_ptr<MeasureValue>>::iterator it = values.begin();

        CHECK_EQUAL("mv1", (*it)->get_name());
        CHECK_EQUAL("Messwert1", (*it)->get_description());
        CHECK_EQUAL(1.234, (*it)->get_value());

        it++;

        CHECK_EQUAL("mv2", (*it)->get_name());
        CHECK_EQUAL("Messwert2", (*it)->get_description());
        CHECK_EQUAL(3.141, (*it)->get_value());

        it++;

        CHECK_EQUAL("mv3", (*it)->get_name());
        CHECK_EQUAL("Messwert3", (*it)->get_description());
        CHECK_EQUAL(2.718, (*it)->get_value());
    }

    TEST_FIXTURE(MeasuresFixture, TestRemoveValueByName)
    {
        CHECK_EQUAL(true, _measures.remove("mv2"));
        list<shared_ptr<MeasureValue>> values = _measures.get_measure_values();
        CHECK_EQUAL(2, values.size());
        list<shared_ptr<MeasureValue>>::iterator it = values.begin();

        CHECK_EQUAL("mv1", (*it)->get_name());
        CHECK_EQUAL("Messwert1", (*it)->get_description());
        CHECK_EQUAL(1.234, (*it)->get_value());

        it++;

        CHECK_EQUAL("mv3", (*it)->get_name());
        CHECK_EQUAL("Messwert3", (*it)->get_description());
        CHECK_EQUAL(2.718, (*it)->get_value());
    }

    TEST_FIXTURE(MeasuresFixture, TestRemoveValueByNameNonexisting)
    {
        CHECK_EQUAL(false, _measures.remove("mv32"));
        list<shared_ptr<MeasureValue>> values = _measures.get_measure_values();
        CHECK_EQUAL(3, values.size());
        list<shared_ptr<MeasureValue>>::iterator it = values.begin();

        CHECK_EQUAL("mv1", (*it)->get_name());
        CHECK_EQUAL("Messwert1", (*it)->get_description());
        CHECK_EQUAL(1.234, (*it)->get_value());

        it++;

        CHECK_EQUAL("mv2", (*it)->get_name());
        CHECK_EQUAL("Messwert2", (*it)->get_description());
        CHECK_EQUAL(3.141, (*it)->get_value());

        it++;

        CHECK_EQUAL("mv3", (*it)->get_name());
        CHECK_EQUAL("Messwert3", (*it)->get_description());
        CHECK_EQUAL(2.718, (*it)->get_value());
    }

    TEST_FIXTURE(MeasuresFixture, TestRemoveValueByValue)
    {
        list<shared_ptr<MeasureValue>> values = _measures.get_measure_values();
        CHECK_EQUAL(3, values.size());
        list<shared_ptr<MeasureValue>>::iterator it = values.begin();
        _measures.remove(*it);

        values = _measures.get_measure_values();
        CHECK_EQUAL(2, values.size());
        it = values.begin();

        CHECK_EQUAL("mv2", (*it)->get_name());
        CHECK_EQUAL("Messwert2", (*it)->get_description());
        CHECK_EQUAL(3.141, (*it)->get_value());

        it++;

        CHECK_EQUAL("mv3", (*it)->get_name());
        CHECK_EQUAL("Messwert3", (*it)->get_description());
        CHECK_EQUAL(2.718, (*it)->get_value());
    }

    TEST_FIXTURE(MeasuresFixture, TestRemoveValueByValueNonexisting)
    {
        list<shared_ptr<MeasureValue>> values;
        list<shared_ptr<MeasureValue>>::iterator it;
        shared_ptr<MeasureValue> value;

        values = _measures.get_measure_values();
        CHECK_EQUAL(3, values.size());
        value = shared_ptr<MeasureValue>(new MeasureValue("mv1",
                                                          "Messwert1",
                                                          1.234));
        CHECK_EQUAL(false, _measures.remove(value));
        values = _measures.get_measure_values();

        CHECK_EQUAL(3, values.size());

        it = values.begin();

        CHECK_EQUAL("mv1", (*it)->get_name());
        CHECK_EQUAL("Messwert1", (*it)->get_description());
        CHECK_EQUAL(1.234, (*it)->get_value());
        it++;

        CHECK_EQUAL("mv2", (*it)->get_name());
        CHECK_EQUAL("Messwert2", (*it)->get_description());
        CHECK_EQUAL(3.141, (*it)->get_value());
        it++;

        CHECK_EQUAL("mv3", (*it)->get_name());
        CHECK_EQUAL("Messwert3", (*it)->get_description());
        CHECK_EQUAL(2.718, (*it)->get_value());
    }

	TEST(DeserializeFromXml)
	{
		shared_ptr<XmlNode> rootMeasuresNode = shared_ptr<XmlNode>(new XmlNode("measures"));
		
		shared_ptr<XmlNode> measureValueNode = shared_ptr<XmlNode>(new XmlNode("measurevalue"));
		measureValueNode->add_attribute(XmlAttribute("name", "length"));
		measureValueNode->add_attribute(XmlAttribute("default", "2.0"));
		measureValueNode->set_text("The length of the square");
		rootMeasuresNode->add_node(measureValueNode);
		
		shared_ptr<XmlNode> measureValueNode2 = shared_ptr<XmlNode>(new XmlNode("measurevalue"));
		measureValueNode2->add_attribute(XmlAttribute("name", "PI"));
		measureValueNode2->add_attribute(XmlAttribute("default", "3.14159"));
		measureValueNode2->set_text("Pie");
		rootMeasuresNode->add_node(measureValueNode2);
		
		shared_ptr<Measures> parsedMeasures = Measures::deserialize_from_xml(rootMeasuresNode);
		
		CHECK_EQUAL(false, parsedMeasures == NULL);
		if(parsedMeasures != NULL)
		{
			list<shared_ptr<MeasureValue>> measureValues = parsedMeasures->get_measure_values();
			CHECK_EQUAL(2, measureValues.size());
			list<shared_ptr<MeasureValue>>::iterator it = measureValues.begin();
			it++;
		}

	}
}
