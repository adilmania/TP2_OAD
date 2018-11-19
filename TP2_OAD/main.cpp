// TP2_OAD.cpp : main project file.

#include "Unit_Form1.h"
#include <time.h>

// using namespace TP2_OAD;

int main(array<System::String ^> ^args)
{

	srand(time(NULL));

	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	TP2_OAD::Unit_Form Unit_Form1;
	System::Windows::Forms::Application::Run(%Unit_Form1);
	
    return 0;
}
