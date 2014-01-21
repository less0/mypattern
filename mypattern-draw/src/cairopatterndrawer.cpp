#include "cairopatterndrawer.h"
#include "pattern.h"

using namespace MyPattern::Base;
using namespace MyPattern::Draw;

CairoPatternDrawer::CairoPatternDrawer(Cairo::RefPtr<Cairo::Context> context)
{
    //ctor
}

CairoPatternDrawer::~CairoPatternDrawer()
{
    //dtor
}

void CairoPatternDrawer::draw(const Part& part)
{
    if(m_cairoContext)
    {

    }
}
