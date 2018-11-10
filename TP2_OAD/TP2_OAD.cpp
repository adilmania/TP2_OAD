// TP2_OAD.cpp : main project file.

#include "jobshop.h"
#include <time.h>

using namespace System;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"TP2 - OAD");
	
	srand(time(NULL));

	std::string ad_file = "LA01.txt";

	T_Probleme un_probleme;
	//T_Solution sol;
	//T_Population pop;
	//T_Population pop2;
	T_Population tab_pop[card_pop];

	lire_instance(ad_file,un_probleme);
	Init_Graphe(un_probleme);

	// Recherche_Locale(un_probleme, SOL, 20);

	// pop2 = Recherche_Locale(un_probleme, sol, pop, 200);

	// Afficher_Vecteur(pop2, un_probleme);

	// std::cout << pop2.cout << std::endl;

	Algorithme_Memetique(un_probleme,tab_pop);

    return 0;
}
