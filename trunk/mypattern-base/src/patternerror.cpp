#include "patternerror.h"

using namespace MyPattern::Base;

PatternError::PatternError(Glib::ustring part_name, Glib::ustring object_name, ObjectType object_type, Glib::ustring message)
{
    this->m_part_name = part_name;
    this->m_object_name = object_name;
    this->m_object_type = object_type;
    this->m_error_message = message;
    this->m_error_code = ERR_GENERAL;
}

PatternError::PatternError(Glib::ustring part_name, Glib::ustring object_name, ObjectType object_type, ErrorCode error_code)
{
    this->m_part_name = part_name;
    this->m_object_name = object_name;
    this->m_object_type = object_type;
    this->m_error_code = error_code;

    this->m_error_message = "";
}

PatternError::PatternError()
{
    this->m_error_code = ERR_OK;
    this->m_error_message = "";
    this->m_object_name = "";
    this->m_part_name = "";
    this->m_object_type = ObjectType::OBJECTTYPE_UNKNOWN;
}

PatternError::~PatternError()
{
}

ErrorCode PatternError::get_error_code()
{
    return this->m_error_code;
}

Glib::ustring PatternError::get_error_message()
{
    return this->m_error_message;
}

Glib::ustring PatternError::get_object_name()
{
    return this->m_object_name;
}

ObjectType PatternError::get_object_type()
{
    return this->m_object_type;
}
