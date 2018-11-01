// TP2_OAD.cpp : main project file.

#include "jobshop.h"

using namespace System;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"TP2 - OAD");

	std::string ad_file = "AD01.txt";

	T_PROBLEME un_probleme;
	T_SOLUS SOL;

	lire_instance(ad_file,un_probleme);

	Evaluer(un_probleme, SOL);
    return 0;
}
