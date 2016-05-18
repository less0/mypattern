#include "cadmainwindow.h"

#include "selectnamewindow.h"
#include "cairopatterndrawer.h"
#include "mypattern-data.h"
#include "mypattern-base.h"

#include <iostream>
#include <limits>
#include <cmath>
#include <gtkmm.h>

using namespace MyPattern::CAD;
using namespace MyPattern::Data;
using namespace MyPattern::Draw;

CADMainWindow::CADMainWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Window(baseObject)
{
    init(builder);
}

CADMainWindow::CADMainWindow() : Gtk::Window()
{
	init();
}

CADMainWindow::~CADMainWindow()
{
    //dtor
}

void CADMainWindow::closeButton_clicked()
{
    this->hide();

    return;
}

void CADMainWindow::buttonAddPart_clicked()
{
    if(!m_selectNameWindow)
    {
        SelectNameWindow* selectNameWindow = 0;

        m_builder->get_widget_derived("wnd-select-name", selectNameWindow);

        selectNameWindow->set_modal();
        selectNameWindow->init(m_builder);

        m_selectNameWindow = shared_ptr<SelectNameWindow>(selectNameWindow);

        m_selectNameWindow->signal_hide().connect(sigc::mem_fun(this, &CADMainWindow::selectNameWindow_addPattern_hide));
    }

    m_selectNameWindow->reset();
    m_selectNameWindow->show_now();

    return;
}

void CADMainWindow::selectNameWindow_addPattern_hide()
{
    if(m_selectNameWindow->get_result())
    {
        m_openedPattern->create_part_definition(m_selectNameWindow->get_text());

        update();
    }
}

bool CADMainWindow::mainDrawingArea_expose(const Cairo::RefPtr<Cairo::Context>& cairo)
{
	MyPattern::Draw::CairoPatternDrawer drawer(cairo, shared_ptr<CoordinateTransformation>(new CoordinateTransformation(10, 10, 50, 50)));
	drawer.set_selected_landmarks(m_selectedLandmarks);
	drawer.set_selected_curves(m_selectedCurves);
	drawer.draw(m_selectedPartDefinition->get_part());

    return true;
}

bool CADMainWindow::init(const Glib::RefPtr<Gtk::Builder>& builder)
{
    m_builder = builder;

    Gtk::ImageMenuItem* item = 0;
    Gtk::ToolButton* tempButton = 0;
    Gtk::ComboBox* comboBox = 0;
    Gtk::DrawingArea* drawingArea = 0;

    this->add_events(Gdk::EventMask::ALL_EVENTS_MASK);

    //get the child widgets
    builder->get_widget("imagemenuitem-close-cad", item);
    builder->get_widget("toolbutton-add-part", tempButton);
    builder->get_widget("combobox1", comboBox);
    builder->get_widget("drawingarea-cad", drawingArea);

    m_partsComboBox = shared_ptr<Gtk::ComboBox>(comboBox);
    m_partsComboBox->pack_start(m_partColumns.column_name);

    m_buttonAddPart = shared_ptr<Gtk::ToolButton>(tempButton);
    this->m_mainDrawingArea = shared_ptr<Gtk::DrawingArea>(drawingArea);

    //connect signals
    item->add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
    //item->signal_button_release_event().connect(sigc::mem_fun(this, &CADMainWindow::closeButton_clicked));

    drawingArea->send_expose(NULL);
    //\todo connect signals
    // drawingArea->signal_draw().connect(sigc::mem_fun(this, &CADMainWindow::mainDrawingArea_expose));
    m_buttonAddPart->signal_clicked().connect(sigc::mem_fun(this, &CADMainWindow::buttonAddPart_clicked));
	//m_buttonAddPart->signal_clicked().connect(sigc::mem_fun(this, &CADMainWindow::buttonAddPart_clicked));
    m_buttonAddPart->add_events(Gdk::EventMask::ALL_EVENTS_MASK);

    m_openedPattern = shared_ptr<PatternDefinition>(new PatternDefinition("Unnamed"));
    m_openedPattern->create_part_definition("Part1");

    update();

    return true;
}

bool CADMainWindow::init() 
{
	CurveDefinition::register_class(shared_ptr<CurveDefinition>(new BezierDefinition()));
	
	m_coordinateTransformation = shared_ptr<CoordinateTransformation>(new CoordinateTransformation(10,10,50,50));
	
	m_mainPane = shared_ptr<Gtk::Paned>(new Gtk::Paned(Gtk::ORIENTATION_VERTICAL));
	
	m_partsComboBox = shared_ptr<Gtk::ComboBox>(new Gtk::ComboBox());
	
	m_mainDrawingArea = shared_ptr<Gtk::DrawingArea>(new Gtk::DrawingArea());
	
	m_mainDrawingArea->show();
	m_mainDrawingArea->override_background_color (Gdk::RGBA("00FFFF"));
	m_mainDrawingArea->signal_draw().connect(sigc::mem_fun(this, &CADMainWindow::mainDrawingArea_expose));
	m_mainDrawingArea->add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
	this->add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
	
	m_openedPattern = PatternDefinition::read_xml("test.xpat");
    m_selectedPartDefinition = m_openedPattern->get_part_definition("Square");
	
	m_partsComboBox->show();
	m_mainPane->show();
	
	m_mainPane->add1(*m_partsComboBox);

	m_mainPane->add2(*m_mainDrawingArea);
	add(*m_mainPane);
	
	m_mainDrawingArea->signal_button_release_event().connect(sigc::mem_fun(this, &CADMainWindow::mainDrawingArea_click));
	
	// testiii = 0;
	
	update();
	
	return true;
}

bool CADMainWindow::mainDrawingArea_click(GdkEventButton* event)
{
	std::cout << "Mousedown" << std::endl;
	Part part = m_selectedPartDefinition->get_part();
	
	list<Point> points = part.get_points();
	list<BezierComplex> curves = part.get_curves();
	
	Point pointWithminimumPointDistance;
	double minimumPointDistance = DBL_MAX;
	BezierComplex curveWithMinimumDistance;
	double minimumCurveDistance = DBL_MAX;
	
	if((event->state & GDK_SHIFT_MASK) == 0)
	{
		std::cout << "Clearing selected landmarks" << std::endl;
		m_selectedLandmarks.clear();
		m_selectedCurves.clear();
	}
	
	for(list<Point>::iterator it = points.begin(); it != points.end(); it++)
	{
		Point currentPoint = m_coordinateTransformation->Transform(*it);
		
		double distance = sqrt((currentPoint.get_x() - event->x) * (currentPoint.get_x() - event->x) + (currentPoint.get_y() - event->y)*(currentPoint.get_y() - event->y));
		
		if(distance < minimumPointDistance)
		{
			pointWithminimumPointDistance = currentPoint;
			minimumPointDistance = distance;
		}
	}
	
	for(list<BezierComplex>::iterator it = curves.begin(); it != curves.end(); it++)
	{
		BezierComplex transformedCurve = m_coordinateTransformation->Transform(*it);
		
		double distance = transformedCurve.get_distance(Point(event->x, event->y));
		
		if(distance < minimumCurveDistance)
		{
			curveWithMinimumDistance = transformedCurve;
			minimumCurveDistance = distance;
		}
	}
	
	if(minimumPointDistance < 5)
	{
		bool wasSelected = false;
		
		for(list<string>::iterator it = m_selectedLandmarks.begin(); it!=m_selectedLandmarks.end(); it++)
		{
			if(*it == pointWithminimumPointDistance.get_landmark_name())
			{
				wasSelected = true;
			}
		}
		
		if(!wasSelected)
		{
			m_selectedLandmarks.push_back(pointWithminimumPointDistance.get_landmark_name());
		}
	}
	else if(minimumCurveDistance < 3)
	{
		bool hasBeenSelectedBefore = false;
		
		for(list<string>::iterator it  = m_selectedCurves.begin(); it != m_selectedCurves.end(); it++)
		{
			if(*it == curveWithMinimumDistance.get_name())
			{
				hasBeenSelectedBefore = true;
			}
		}
		
		if(!hasBeenSelectedBefore)
		{
			m_selectedCurves.push_back(curveWithMinimumDistance.get_name());
			std::cout << "Selected Curve: " << curveWithMinimumDistance.get_name() << std::endl;;
		}
	}
	
	
	
	
	update();
	
	return false;
}

void CADMainWindow::update()
{
    list<string> part_definition_names = m_openedPattern->get_part_defintion_names();
    list<string>::iterator it_names = part_definition_names.begin();

    m_partsComboBox->set_model(m_partNamesTreestore = Gtk::TreeStore::create(m_partColumns));

    while(it_names != part_definition_names.end())
    {
		std::cout << *it_names << std::endl;
		
        Gtk::TreeModel::Row row = *(m_partNamesTreestore->append());
        row[m_partColumns.column_name] = *it_names;
        row[m_partColumns.column_pattern] = shared_ptr<MyPattern::Base::PatternDefinition>((MyPattern::Base::PatternDefinition*)NULL);

        it_names++;
    }

    // force our program to redraw
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, true);
    }
}
















