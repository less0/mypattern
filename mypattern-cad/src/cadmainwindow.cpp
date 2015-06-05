#include "cadmainwindow.h"

#include "selectnamewindow.h"
#include "cairopatterndrawer.h"
#include "mypattern-data.h"
#include "mypattern-base.h"

#include <iostream>

using namespace MyPattern::CAD;
using namespace MyPattern::Data;

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
    // cairo->move_to(0,0);
    // cairo->curve_to(50,0, 50,100,100,100);
    // cairo->stroke();
	
	MyPattern::Draw::CairoPatternDrawer drawer(cairo);
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
//    m_buttonAddPart->signal_clicked().connect(sigc::mem_fun(this, &CADMainWindow::buttonAddPart_clicked));
    m_buttonAddPart->add_events(Gdk::EventMask::ALL_EVENTS_MASK);

    m_openedPattern = shared_ptr<PatternDefinition>(new PatternDefinition("Unnamed"));
    m_openedPattern->create_part_definition("Part1");

    update();

    return true;
}

bool CADMainWindow::init() 
{
	CurveDefinition::register_class(shared_ptr<CurveDefinition>(new BezierDefinition()));
	
	m_mainPane = shared_ptr<Gtk::Paned>(new Gtk::Paned(Gtk::ORIENTATION_VERTICAL));
	
	m_partsComboBox = shared_ptr<Gtk::ComboBox>(new Gtk::ComboBox());
	
	m_mainDrawingArea = shared_ptr<Gtk::DrawingArea>(new Gtk::DrawingArea());
	
	m_mainDrawingArea->signal_draw().connect(sigc::mem_fun(this, &CADMainWindow::mainDrawingArea_expose));
	m_mainDrawingArea->show();
	m_mainDrawingArea->override_background_color (Gdk::RGBA("00FFFF"));
	
	m_openedPattern = PatternDefinition::read_xml("test.xpat");
    m_selectedPartDefinition = m_openedPattern->get_part_definition("Square");
	
	m_partsComboBox->show();
	m_mainPane->show();
	
	m_mainPane->add1(*m_partsComboBox);
	m_mainPane->add2(*m_mainDrawingArea);
	add(*m_mainPane);
	
	update();
	
	return true;
}

void CADMainWindow::update()
{
    list<Glib::ustring> part_definition_names = m_openedPattern->get_part_defintion_names();
    list<Glib::ustring>::iterator it_names = part_definition_names.begin();

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
