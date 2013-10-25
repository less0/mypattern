#include "pattern.h"

using namespace MyPattern::Base;

Pattern::Pattern()
{
    //ctor
}

void Pattern::set_name(Glib::ustring name)
{
    m_name = name;
}

Glib::ustring Pattern::get_name()
{
    return m_name;
}

void Pattern::add_part(Part part)
{
    m_parts.push_back(part);
}
