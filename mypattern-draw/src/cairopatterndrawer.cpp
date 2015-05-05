#include "cairopatterndrawer.h"
#include "pattern.h"

using namespace MyPattern::Base;
using namespace MyPattern::Draw;

CairoPatternDrawer::CairoPatternDrawer(Cairo::RefPtr<Cairo::Context> context)
{
    m_cairoContext = context;
}

CairoPatternDrawer::~CairoPatternDrawer()
{
    //dtor
}

void CairoPatternDrawer::draw(Part part)
{
    if(m_cairoContext)
    {
		list<Point> points = part.get_points();
		
		for(list<Point>::iterator it = points.begin(); it != points.end(); it++)
		{
			int x = it->get_x() * 50.0;
			int y = it->get_y() * 50.0;
			
			m_cairoContext->move_to(x-5,y-5);
			m_cairoContext->line_to(x+5,y-5);
			m_cairoContext->line_to(x+5,y+5);
			m_cairoContext->line_to(x-5,y+5);
			m_cairoContext->line_to(x-5,y-5);
			m_cairoContext->stroke();
			
		}
		
		list<BezierComplex> curves = part.get_curves();
		
		for(list<BezieComplex>::iterator it_curve = curves.begin(); it_curve!=curves.end(); it_curve++)
		{
			
		}
    }
}


void CairoPatternDrawer::draw_page(MyPattern::Base::Part, int, int)
{
}

MyPattern::Draw::Size CairoPatternDrawer::get_size(MyPattern::Base::Part)
{
	return Size();
}