#include <array>

#include "cairopatterndrawer.h"
#include "pattern.h"
#include "bezier.h"
#include "beziercomplex.h"
#include "point.h"

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
		
		for(list<BezierComplex>::iterator it_curve = curves.begin(); it_curve!=curves.end(); it_curve++)
		{
			list<Bezier> base_curves = it_curve->get_beziers();
			for(list<Bezier>::iterator it_base_curve = base_curves.begin(); it_base_curve != base_curves.end(); it_base_curve++)
			{
				array<Point,4> points = it_base_curve->get_points();
				
				m_cairoContext->move_to(points[0].get_x() * 50.0, points[0].get_y() *  50.0);
				m_cairoContext->curve_to(points[1].get_x() * 50.0, points[1].get_y() * 50.0,points[2].get_x() * 50.0, points[2].get_y() * 50.0,points[3].get_x() * 50.0, points[3].get_y() * 50.0);
				m_cairoContext->stroke();
			}
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