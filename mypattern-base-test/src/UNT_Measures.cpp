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
}
