#include "landmark.h"

#include <sstream>

Landmark::Landmark()
{
    m_name = "";
    m_x_definition = "";
    m_y_definition = "";
}

Landmark::~Landmark()
{
    //dtor
}


bool Landmark::set_name(Glib::ustring name)
{
    if(this->m_signal_name_change_request.emit(name, ObjectType::PARTTYPE_LANDMARK))
    {
        this->m_name = name;
        return true;
    }

    return false;
}

Glib::ustring Landmark::get_name()
{
    return this->m_name;
}

Glib::ustring Landmark::get_xml()
{
    stringstream result;

    result << "<landmark name=\"" + get_name() + "\" ";
    result << "x=\"" + get_definition_x() + "\" ";
    result << "y=\"" + get_definition_y() + "\" ";
    result << " />" << std::endl;

    return Glib::ustring(result.str());
}

