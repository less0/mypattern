#ifndef SELECTNAMEWINDOW_H
#define SELECTNAMEWINDOW_H

#include <gtkmm.h>
#include <memory>

using namespace std;

class SelectNameWindow : public Gtk::Dialog
{
    public:
        SelectNameWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder);
        ~SelectNameWindow();

        void init(const Glib::RefPtr<Gtk::Builder>& builder);
        Glib::ustring get_text();
        bool get_result();
        void reset();
    protected:
    private:
        bool m_result = false;
        shared_ptr<Gtk::Entry> m_textBox;

        void buttonOk_clicked();
        void buttonCancel_clicked();
};

#endif // SELECTNAMEWINDOW_H
