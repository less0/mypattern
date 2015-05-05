#include "program.h"
#include "patterncolumnrecord.h"

using namespace MyPattern::CAD;

Program::Program(int argc, char* argv[])
{
    m_main_object = new Main(argc, argv);
    // RefPtr<Builder> builder = Builder::create_from_file("mypattern-cad.glade");

    // builder->get_widget_derived("wnd-my-pattern-cad", m_main_window);
	m_main_window = new CADMainWindow();
}

int Program::run()
{
    //show up the main window
    m_main_object->run(*m_main_window);

    delete m_main_object;

    return 0;
}


Program::~Program()
{
//    delete m_main_object;
}
