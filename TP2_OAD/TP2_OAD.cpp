// TP2_OAD.cpp : main project file.

#include "jobshop.h"
#include <time.h>

using namespace System;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"TP2 - OAD");
	
	srand(time_t(NULL));
	int iter_max;
	T_Probleme un_probleme;
	T_Solution sol;
	
	std::string ad_file = "LA01.txt";
	lire_instance(ad_file, un_probleme);
	Init_Graphe(un_probleme);

	T_Population tab_pop[card_pop];
	Init_Tab_Pop(tab_pop);

	T_Population pop;
	T_Population pop2;

	// Generer_Population(tab_pop, un_probleme);
	// std::cout << "On passe a autre chose" << std::endl;

	// Recherche_Locale(un_probleme, SOL, 20);

	// pop2 = Recherche_Locale(un_probleme, sol, pop, itermax);

	// Afficher_Vecteur(pop2, un_probleme);

	// std::cout << pop2.cout << std::endl;

	std::cout << std::endl << "Entrez le nombre d'iteration?" << std::endl;
	std::cin >> iter_max;
	Algorithme_Memetique(un_probleme, tab_pop, iter_max);
	std::cout << "Le makespan vaut: " << tab_pop[0].cout << std::endl;

	//T_Solution sol;
	//T_Population pop;
	//T_Population pop2;
	
	// Generer_Population(tab_pop, un_probleme);
	// std::cout << "On passe a autre chose" << std::endl;

	// Recherche_Locale(un_probleme, SOL, 20);

	// pop2 = Recherche_Locale(un_probleme, sol, pop, 200);

	// Afficher_Vecteur(pop2, un_probleme);

	// std::cout << pop2.cout << std::endl;


    return 0;
}
