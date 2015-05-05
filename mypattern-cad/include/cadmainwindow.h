#ifndef CADMAINWINDOW_H
#define CADMAINWINDOW_H

#include "gtkmm.h"
#include "glibmm/ustring.h"
#include "gtkmm/widget.h"
#include "gdkmm/window.h"
#include "patterncolumnrecord.h"
#include "patterndefinition.h"
#include "partdefinition.h"
#include "selectnamewindow.h"
#include <memory>

using namespace MyPattern::Base;
using namespace std;

namespace MyPattern
{
    namespace CAD
    {
        class CADMainWindow : public Gtk::Window
        {
            public:
                CADMainWindow(BaseObjectType* base, const Glib::RefPtr<Gtk::Builder>& builder);
                CADMainWindow();
                virtual ~CADMainWindow();
                void closeButton_clicked();
                bool newButton_clicked(GdkEventButton* e);
                bool openFileButton_clicked(GdkEventButton* e);
                bool saveButton_clicked(GdkEventButton* e);
                bool saveAsButtonClicked(GdkEventButton* e);
                void buttonAddPart_clicked();
                void selectNameWindow_addPattern_hide();
                bool mainDrawingArea_expose(const Cairo::RefPtr<Cairo::Context>&);
                /** \brief Gets the widgets loaded in builder and connects the signals
                */
                bool init(const Glib::RefPtr<Gtk::Builder>& builder);
				bool init();

                static void test();
            protected:
            private:
                Glib::RefPtr<Gtk::TreeStore> m_partNamesTreestore;
                Glib::RefPtr<Gtk::Builder> m_builder;

                shared_ptr<PatternDefinition> m_openedPattern;
				shared_ptr<PartDefinition> m_selectedPartDefinition;
				
                shared_ptr<Gtk::ComboBox> m_partsComboBox;
                shared_ptr<Gtk::ToolButton> m_buttonAddPart;
                shared_ptr<Gtk::DrawingArea> m_mainDrawingArea;

                shared_ptr<SelectNameWindow> m_selectNameWindow;
				shared_ptr<Gtk::Paned> m_mainPane;

                bool m_patternSaved = true;
                PartColumnRecord m_partColumns;

                void update();
        };
    }
}


#endif // CADMAINWINDOW_H
