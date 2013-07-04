#ifndef CADMAINWINDOW_H
#define CADMAINWINDOW_H

#include "gtkmm.h"
#include "glibmm/ustring.h"


class CADMainWindow : public Gtk::Window
{
    public:
        CADMainWindow(BaseObjectType* base, const Glib::RefPtr<Gtk::Builder>& builder);
        virtual ~CADMainWindow();
        bool closeButton_clicked(GdkEventButton* e);
        bool newButton_clicked(GdkEventButton* e);
        bool openFileButton_clicked(GdkEventButton* e);
        bool saveButton_clicked(GdkEventButton* e);
        bool saveAsButtonClicked(GdkEventButton* e);
        /** \brief Gets the widgets loaded in builder and connects the signals
        */
        bool init(const Glib::RefPtr<Gtk::Builder>& builder);
    protected:
    private:
};

#endif // CADMAINWINDOW_H
