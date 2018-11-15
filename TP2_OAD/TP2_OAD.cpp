// TP2_OAD.cpp : main project file.

#include "Unit_JobShop.h"
#include <time.h>

using namespace System;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"TP2 - OAD");
	
	srand(time(NULL));

	int iter_max;

	T_PROBLEME un_probleme;
	T_SOLUTION une_solution;
	
	std::string ad_file = "LA01.txt";

	Init_Probleme(un_probleme);
	Lecture_Fichier(ad_file, un_probleme);
	Remplir_Probleme(un_probleme);

	std::cout << un_probleme.m << std::endl;
	T_POPULATION Tab_Pop[CARD_POP];
	Init_Population(Tab_Pop);

	std::cout << std::endl << "Entrez le nombre d'iteration?" << std::endl;
	std::cin >> iter_max;
	Algorithme_Memetique(un_probleme, Tab_Pop, iter_max);
	std::cout << "Le makespan vaut: " << Tab_Pop[0].Cout << std::endl;
	
    return 0;
}
