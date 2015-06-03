#include <gtkmm.h>
#include <iostream>
#include <exception.h>
#include "program.h"
#ifdef WIN32
	#include <windows.h>
#endif

using namespace std;
using namespace Gtk;
using namespace MyPattern::Exceptions;

int main(int argc, char* argv[]);

//Define Windows entry point to the application
#ifdef WIN32

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// check windows version
    DWORD dwVersion = GetVersion();

    if (!(dwVersion < 0x80000000))
    {
        MessageBox(0, _WCHAR_T("This application requires Windows 2000/XP or above!"), _WCHAR_T("Fatal Error"), MB_OK);
        return -1;
    }

    //execute main function
    return main(__argc, __argv);
}

#endif

//The conventional main function will be used if compiling under linux
int main(int argc, char *argv[])
{
    int return_value;

	try
	{
		MyPattern::CAD::Program prog(argc,argv);
		return_value = prog.run();
	}
	catch(MyPattern::Exceptions::Exception& exception)
	{
		std::cout << exception.get_type() << ": " << exception.get_message() << std::endl;
		return_value = 1001;
	}
    

    return return_value;
}
