#include "size.h"

using namespace MyPattern::Base;

Size::Size()
{
    //ctor
    this->m_width = .0f;
    this->m_height = .0f;
}

Size::Size(float width, float height)
{
    this->m_width = width;
    this->m_height = height;
}

Size::~Size()
{
    //dtor
}
