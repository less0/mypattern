#include "cadmainwindow.h"

#include "selectnamewindow.h"

using namespace MyPattern::CAD;

CADMainWindow::CADMainWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Window(baseObject)
{
    init(builder);
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

bool CADMainWindow::mainDrawingArea_expose(GdkEventExpose* e)
{
    int i = 0;
    Cairo::RefPtr<Cairo::Context> cairo = m_mainDrawingArea->get_window()->create_cairo_context();

    cairo->move_to(0,0);
    cairo->curve_to(50,0, 50,100,100,100);
    cairo->stroke();

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
    drawingArea->signal_expose_event().connect(sigc::mem_fun(this, &CADMainWindow::mainDrawingArea_expose));
    m_buttonAddPart->signal_clicked().connect(sigc::mem_fun(this, &CADMainWindow::buttonAddPart_clicked));
//    m_buttonAddPart->signal_clicked().connect(sigc::mem_fun(this, &CADMainWindow::buttonAddPart_clicked));
    m_buttonAddPart->add_events(Gdk::EventMask::ALL_EVENTS_MASK);

    m_openedPattern = shared_ptr<PatternDefinition>(new PatternDefinition("Unnamed"));
    m_openedPattern->create_part_definition("Part1");

    update();

    return true;
}

void CADMainWindow::update()
{
    list<Glib::ustring> part_definition_names = m_openedPattern->get_part_defintion_names();
    list<Glib::ustring>::iterator it_names = part_definition_names.begin();

    //m_part_names_treestore->clear();

    m_partsComboBox->set_model(m_partNamesTreestore =  Gtk::TreeStore::create(m_partColumns));


    while(it_names != part_definition_names.end())
    {
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

    int i=0;
}
