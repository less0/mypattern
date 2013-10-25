#include "measurevalue.h"

using namespace MyPattern::Base;

MeasureValue::MeasureValue(Glib::ustring name, Glib::ustring description, double value)
{
    this->m_name = name;
    this->m_description = description;
    this->m_value = value;
}

MeasureValue::MeasureValue(const MeasureValue& valueToCopy)
{
    this->m_name = valueToCopy.m_name;
    this->m_description = valueToCopy.m_description;
    this->m_value = valueToCopy.m_value;

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
    return this->m_value;
}

void MeasureValue::set_value(double value)
{
    this->m_value = value;
}


