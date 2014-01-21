#include "selectnamewindow.h"

SelectNameWindow::SelectNameWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Dialog(baseObject)
{
}

SelectNameWindow::~SelectNameWindow()
{
    //dtor
}

void SelectNameWindow::init(const Glib::RefPtr<Gtk::Builder>& builder)
{
    Gtk::Button *buttonOk = 0,
        *buttonCancel = 0;

    Gtk::Entry* textBox = 0;

    builder->get_widget("wnd-select-name-button-ok", buttonOk);
    builder->get_widget("wnd-select-name-button-cancel", buttonCancel);
    builder->get_widget("wnd-select-name-entry-name", textBox);
    m_textBox = shared_ptr<Gtk::Entry>(textBox);

    buttonCancel->signal_clicked().connect(sigc::mem_fun(this, &SelectNameWindow::buttonCancel_clicked));
    buttonOk->signal_clicked().connect(sigc::mem_fun(this, &SelectNameWindow::buttonOk_clicked));
}

void SelectNameWindow::reset()
{
    this->m_result = false;
    this->m_textBox->set_text("");
}

//event handler
void SelectNameWindow::buttonOk_clicked()
{
    this->m_result = true;
    this->hide();
}

void SelectNameWindow::buttonCancel_clicked()
{
    this->m_result = false;
    this->hide();
}



Glib::ustring SelectNameWindow::get_text()
{
    return m_textBox->get_text();
}

bool SelectNameWindow::get_result()
{
    return this->m_result;
}
