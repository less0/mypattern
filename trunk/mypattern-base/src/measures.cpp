#include "measures.h"

using namespace MyPattern::Base;

Measures::Measures()
{
}

Measures::~Measures()
{
}

shared_ptr<MeasureValue> Measures::define(Glib::ustring name, Glib::ustring comment, double default_value)
{
	shared_ptr<MeasureValue> value_to_add = shared_ptr<MeasureValue>(new MeasureValue(name, comment, default_value));

	m_measureValues.push_back((value_to_add));

return value_to_add;	
}

list<shared_ptr<MeasureValue>> Measures::get_measure_values()
{
	return m_measureValues;
}
