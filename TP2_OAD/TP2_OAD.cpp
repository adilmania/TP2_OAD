// TP2_OAD.cpp : main project file.

#include "jobshop.h"
#include <time.h>

using namespace System;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"TP2 - OAD");
	
	srand(time(NULL));

	std::string ad_file = "AD01.txt";

	T_PROBLEME un_probleme;
	T_SOLUS SOL;
	int makespan;
	int dern;

	lire_instance(ad_file,un_probleme);
	
	// Recherche_Locale(un_probleme, SOL, 20);

	Evaluer(un_probleme, SOL);
    return 0;
}
