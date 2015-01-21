#include "measures.h"

#include "exceptions/argumentexception.h"

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

bool Measures::remove(ustring name)
{
    bool result = false;

    for(list<shared_ptr<MeasureValue>>::iterator it = m_measureValues.begin();
        it != m_measureValues.end();
        it++)
    {
        if((*it)->get_name() == name)
        {
            m_measureValues.remove(*it);
            result = true;
            break;
        }
    }

    return result;
}

bool Measures::remove(shared_ptr<MeasureValue> valueToRemove)
{
    bool found = false;

    for(list<shared_ptr<MeasureValue>>::iterator it = m_measureValues.begin();
        ! found && it != m_measureValues.end();
        it++)
    {
        if(*it == valueToRemove)
        {
            m_measureValues.remove(*it);
            found = true;
        }
    }

    return found;
}

shared_ptr<Measures> Measures::deserialize_from_xml(shared_ptr<XmlNode> measuresNode)
{
	if(measuresNode->get_name() != "measures")
	{
		throw ArgumentException("Could not parse measures");
	}
	
	shared_ptr<Measures> parsedMeasures = shared_ptr<Measures>(new Measures());
	
	list<shared_ptr<XmlNode>> subnodes =  measuresNode->get_nodes();
	
	for(list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();
		it != subnodes.end();
		it++)
	{
		if((*it)->get_name() == "measurevalue")
		{
			parsedMeasures->m_measureValues.push_back(MeasureValue::deserialize_from_xml(*it));
		}
	}
	
	return parsedMeasures;
}