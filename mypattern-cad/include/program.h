#ifndef PROGRAM_H
#define PROGRAM_H

#include "gtkmm.h"
#include "glibmm.h"
#include "cadmainwindow.h"

using namespace Gtk;
using namespace Glib;

/*! \brief Main object for the mypattern-cad Program
*
* This class initializes all other objects needed to run the mypattern-cad Program and stores the project and system variables.
*/
class Program
{
    public:
        Program(int argc, char* argv[]);
        virtual ~Program();
        /*! \brief Executes the Gtk::Main object which will cause the program to jump into the Gtk event handling loop
        */
        int run();
        bool close(GdkEventButton* event);
    protected:
    private:
        DrawingArea*    m_drawingArea; ///\todo check if this is needed
        CADMainWindow*  m_main_window;
        Main*           m_main_object;
        ImageMenuItem*  m_close_imagemenuitem;
};

#endif // PROGRAM_H
