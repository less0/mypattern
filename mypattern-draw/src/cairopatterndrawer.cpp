#include <array>

#include "cairopatterndrawer.h"
#include "pattern.h"
#include "bezier.h"
#include "beziercomplex.h"
#include "point.h"

using namespace MyPattern::Base;
using namespace MyPattern::Draw;

CairoPatternDrawer::CairoPatternDrawer(Cairo::RefPtr<Cairo::Context> context, shared_ptr<CoordinateTransformation> coordinateTransformation)
{
    m_cairoContext = context;
	m_coordinateTransformation = coordinateTransformation;
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
			Point p = m_coordinateTransformation->Transform(*it);
			
			int x = p.get_x();
			int y = p.get_y();
			
			m_cairoContext->move_to(x-5,y-5);
			m_cairoContext->line_to(x+5,y-5);
			m_cairoContext->line_to(x+5,y+5);
			m_cairoContext->line_to(x-5,y+5);
			m_cairoContext->line_to(x-5,y-5);
			
			for(list<Glib::ustring>::iterator it_selected_landmark = m_selectedLandmarks.begin(); it_selected_landmark != m_selectedLandmarks.end(); it_selected_landmark++)
			{
				if(*it_selected_landmark == p.get_landmark_name())
				{
					m_cairoContext->set_source_rgb(1.0, .0, .0);
				}
			}
			
			m_cairoContext->stroke();
			m_cairoContext->set_source_rgb(.0, .0, .0);
			
		}
		
		list<BezierComplex> curves = part.get_curves();
		
		for(list<BezierComplex>::iterator it_curve = curves.begin(); it_curve!=curves.end(); it_curve++)
		{
			list<Bezier> base_curves = it_curve->get_beziers();
			for(list<Bezier>::iterator it_base_curve = base_curves.begin(); it_base_curve != base_curves.end(); it_base_curve++)
			{
				array<Point,4> points = it_base_curve->get_points();
				
				for(int i = 0; i < 4; i++)
				{
					points[i] = m_coordinateTransformation->Transform(points[i]);
				}
				
				m_cairoContext->move_to(points[0].get_x(), points[0].get_y());
				m_cairoContext->curve_to(points[1].get_x(), points[1].get_y(),points[2].get_x(), points[2].get_y(),points[3].get_x(), points[3].get_y());
				
				for(list<Glib::ustring>::iterator it_selected_curve = m_selectedCurves.begin(); it_selected_curve != m_selectedCurves.end(); it_selected_curve++)
				{
					if(*it_selected_curve == it_curve->get_name())
					{
						m_cairoContext->set_source_rgb(1.0, .0, .0);
					}
				}
				
				m_cairoContext->stroke();
				m_cairoContext->set_source_rgb(.0, .0, .0);
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

void CairoPatternDrawer::set_selected_landmarks(list<Glib::ustring> selectedLandmarks)
{
	m_selectedLandmarks = selectedLandmarks;
}

void CairoPatternDrawer::set_selected_curves(list<Glib::ustring> selectedCurves)
{
	m_selectedCurves = selectedCurves;
}