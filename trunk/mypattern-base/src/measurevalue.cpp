#include "measurevalue.h"

using namespace MyPattern::Base;

MeasureValue::MeasureValue(Glib::ustring name, Glib::ustring description, double value)
{
    this->m_name = name;
    this->m_description = description;
    this->m_default_value = value;
    this->m_has_value = false;
}

MeasureValue::MeasureValue(const MeasureValue& valueToCopy)
{
    this->m_name = valueToCopy.m_name;
    this->m_description = valueToCopy.m_description;
    this->m_value = valueToCopy.m_value;
    this->m_default_value = valueToCopy.m_default_value;
    this->m_has_value = valueToCopy.m_has_value;
}

MeasureValue::~MeasureValue()
{
    //dtor
}

Glib::ustring MeasureValue::get_name()
{
    return this->m_name;
}

Glib::ustring MeasureValue::get_description()
{
    return this->m_description;
}

double MeasureValue::get_value()
{
    return m_has_value ? this->m_value : m_default_value;
}

void MeasureValue::set_value(double value)
{
    this->m_value = value;
    this->m_has_value = true;

    if(!signal_changed.empty())
        signal_changed.emit();
}

double parse(ustring);

shared_ptr<MeasureValue> MeasureValue::deserialize_from_xml(shared_ptr<XmlNode> measureValueNode)
{
	if(measureValueNode->get_name() != "measurevalue")
	{
		throw MyPattern::Exceptions::Exception();
	}
	
	ustring name = "";
	double value = .0;
	ustring description = "";
	
	list<XmlAttribute> attributes = measureValueNode->get_attributes();
	
	for(list<XmlAttribute>::iterator it = attributes.begin(); it != attributes.end(); it++)
	{
		if(it->get_name() == "name")
		{
			name = it->get_value();
		}
		else if(it->get_name() == "default")
		{
			value = parse(it->get_value());
		}
	}
	
	description = measureValueNode->get_text();
	
	shared_ptr<MeasureValue> parsedMeasureValue = shared_ptr<MeasureValue>(new MeasureValue(name, description, value));
	
	return parsedMeasureValue;
}

double parse(ustring in)
{
	//TODO check if number is formatted correctly

	stringstream s(in);
	double value;
    s >> value;
	return value;
}