#include "patternobject.h"

using namespace MyPattern::Base;

PatternObject::PatternObject(ObjectType type)
{
    m_type = type;
}

PatternObject::PatternObject()
{
}

PatternObject::~PatternObject()
{
}

//
//PatternObject::PatternObject(const PatternObject& base)
//{
//    m_name = base.m_name;
//    m_type = base.m_type;
//}
//
//PatternObject::~PatternObject()
//{
//    //dtor
//}
//
//void PatternObject::set_object_name(string name)
//{
//    m_name = name;
//}
//
//string PatternObject::get_object_name()
//{
//    return m_name;
//}
//
//void PatternObject::set_object_type(ObjectType type)
//{
//    m_type = type;
//}
//
//ObjectType PatternObject::get_object_type()
//{
//    return m_type;
//}
