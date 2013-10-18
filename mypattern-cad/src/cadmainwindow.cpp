#include "cadmainwindow.h"

CADMainWindow::CADMainWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Window(baseObject)
{
    init(builder);
}

CADMainWindow::~CADMainWindow()
{
    //dtor
}

bool CADMainWindow::closeButton_clicked(GdkEventButton* e)
{
    this->hide();

    return false;
}

bool CADMainWindow::init(const Glib::RefPtr<Gtk::Builder>& builder)
{
    Gtk::ImageMenuItem* item = 0;

    //get the child widgets
    builder->get_widget("imagemenuitem-close-cad", item);

    //connect signals
    item->signal_button_release_event().connect(sigc::mem_fun(this, &CADMainWindow::closeButton_clicked));

    return true;
}
