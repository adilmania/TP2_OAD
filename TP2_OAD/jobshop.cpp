#include "stdafx.h"
#include "jobshop.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Fonction permettant de lire une instance à partir d'un fichier

/*
void lire_instance(std::string ad_file, T_Probleme &un_probleme)
{
	ifstream fichier(ad_file, ios::in);  // on ouvre le fichier en lecture

	if (fichier)  // si l'ouverture a réussi
	{
		std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
		getline(fichier, contenu);  // on met dans "contenu" la ligne

		stringstream ss(contenu);

		ss >> un_probleme.n;
		ss >> un_probleme.m;

		std::cout << "Nombre de Pieces: " << un_probleme.n << endl;
		std::cout << "Nombre de Machines: " << un_probleme.m << endl;

		std::cout << endl << "Affichage du fichier lu" << endl;

		int c, compteur, j;

		for (int i = 1; i <= un_probleme.n; i++)
		{
			// Lecture ligne par ligne
			getline(fichier, contenu);
			std::cout << contenu << endl;

			// Lecture caractère par caractère
			compteur = 0;
			j = 1;

			stringstream ss2(contenu);

			while (ss2 >> c)
			{
				// cout << c << endl;
				if (compteur % 2 == 0)
				{
					un_probleme.Mach[i][j] = c + 1; // c+1 avant
				}
				else
				{
					un_probleme.P[i][j] = c;
					j++;
				}
				compteur++;
			}
		}

		fichier.close();  // on ferme le fichier
	}
	else  // sinon
	{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}
*/

/*
void Init_Graphe(T_Probleme &un_probleme) {
	int i, j, compteur;
	std::cout << "Affichage M" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << un_probleme.Mach[i][j] << " ";
		}
		std::cout << endl;
	}

	std::cout << "Affichage P" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << un_probleme.P[i][j] << " ";
		}
		std::cout << endl;
	}

	// Init T
	compteur = 1;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			un_probleme.T[i][j] = compteur;
			compteur++;
		}
	}

	std::cout << "Affichage T" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << un_probleme.T[i][j] << " ";
		}
		std::cout << endl;
	}

	// Init P_INV
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			un_probleme.P_inv[i][un_probleme.Mach[i][j]] = un_probleme.P[i][j];
		}
	}

	std::cout << "Affichage P_INV" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << un_probleme.P_inv[i][j] << " ";
		}
		std::cout << endl;
	}

	// Init T_INV
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			un_probleme.T_inv[i][un_probleme.Mach[i][j]] = un_probleme.T[i][j];
			// std::cout << "i= " << i << " j= " << j << " " << " Mach[i][j]= " << un_probleme.Mach[i][j] << " T[i][j]= " << T[i][j] << " T_INV[i][Mach[i][j]]= " << T_inv[i][un_probleme.Mach[i][j]] << " " << std::endl;
		}
	}

	std::cout << "Affichage T_INV" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << un_probleme.T_inv[i][j] << " ";
		}
		std::cout << endl;
	}

}
*/

/*
// Fonction permettant de génerer un vecteur de Bierwith

void Generer_Vecteur(T_Population &pop, T_Probleme &un_probleme)
{
	int i;
	int tab[taille_vecteur] = { 0 };
	int nb_operations = un_probleme.n * un_probleme.m;

	pop.vecteur[0] = 999;

	for (i = 1; i <= nb_operations; i++)
	{
		do
		{
			pop.vecteur[i] = (int)(rand() % un_probleme.n) + 1;
		} while (tab[pop.vecteur[i]] >= (un_probleme.m));

		tab[pop.vecteur[i]]++;

	}
	// Afficher_Vecteur(pop, un_probleme);
}

void Afficher_Vecteur(T_Population &pop, T_Probleme &un_probleme)
{
	int i;
	int nb_operations = un_probleme.n * un_probleme.m;
	printf("Vecteur de Bierwith : ");
	for (i = 1; i < nb_operations + 1; i++) {
		printf("%d ", pop.vecteur[i]);
	}
	printf("\n");
}

// Fonction Evaluer 
void Evaluer(T_Probleme &un_probleme, T_Solution &sol, T_Population &pop, int &finCheminCritique) {
	pop.cout = 0;
	int i, k, prec, date, mach, cour, pos;
	int prod = un_probleme.n * un_probleme.m;
	int NP[nmax] = { 0 };
	int m[mmax] = { 0 };

	// Generation d'un Vecteur de Bierwith Aleatoire

	Generer_Vecteur(pop, un_probleme);

	// ALGO
	for (i = 1; i <= prod; i++)
	{
		k = pop.vecteur[i];
		NP[k]++;

		if (NP[k] > 1) {
			prec = sol.ES[un_probleme.T[k][NP[k] - 1]];
			date = prec + un_probleme.P[k][NP[k] - 1];
			if (date > sol.ES[un_probleme.T[k][NP[k] - 1]])
			{
				sol.ES[un_probleme.T[k][NP[k]]] = date;
				cour = un_probleme.T[k][NP[k]];
				pos = un_probleme.T[k][NP[k]-1];
				sol.PERE[cour] = pos;
			}
		}

		mach = un_probleme.Mach[k][NP[k]];

		if (m[mach] > 0) {
			prec = sol.ES[un_probleme.T_inv[m[mach]][mach]];
			if (prec + un_probleme.P_inv[m[mach]][mach] > sol.ES[un_probleme.T[k][NP[k]]])
			{
				sol.ES[un_probleme.T[k][NP[k]] ] = prec + un_probleme.P_inv[m[mach]][mach];
				cour = un_probleme.T[k][NP[k]];
				pos = un_probleme.T_inv[m[mach]][mach];
				sol.PERE[cour] = pos;
			}
		}
		m[mach] = k;
	}

	// Calcul du cout (makespan)
	for (i = 1; i <= un_probleme.n; i++) {
		if (pop.cout<sol.ES[i*un_probleme.m]+un_probleme.P[i][un_probleme.m]) {
			pop.cout = sol.ES[i*un_probleme.m] + un_probleme.P[i][un_probleme.m];
			finCheminCritique = i*un_probleme.m;
		}
	}
}

// Fonction Initialiation Tableau Appartient
void Initialiser_Tableau_APP(T_Probleme &un_probleme, int APP[ntotal + 1]) {
	int k = 1;
	int t = 1;
	int eps;
	int prod = un_probleme.n * un_probleme.m;

	// Initialisation Tableau APP
	APP[0] = 999;

	while (t <= prod)
	{
		eps = 0;
		while (eps < un_probleme.m) {
			APP[t + eps] = k;
			eps++;
		}
		k++;
		t += eps;
	}
}

// Fonction Permutation Arc Disjonctif
void Swap_Arc_Disjonctif(T_Probleme &un_probleme, int i, int j, T_Population &pop, T_Population &pop2) {

	//Afficher_Vecteur(pop, un_probleme);
	//Afficher_Vecteur(pop2, un_probleme);

	int qi, ri, qj, rj;

	int compteuri = 1, compteurj = 1;
	int ki = 1, kj = 1;
	int temp;

	i--;
	j--;

	qi = (i / un_probleme.m) + 1;
	ri = (i % un_probleme.m) + 1;

	qj = (j / un_probleme.m) + 1;
	rj = (j % un_probleme.m) + 1;

	while (compteuri <= ri) {
		if (pop.vecteur[ki] == qi) {
			compteuri++;
		}
		ki++;
	}
	ki--;

	while (compteurj <= rj) {
		if (pop.vecteur[kj] == qj) {
			compteurj++;
		}
		kj++;
	}
	kj--;

	temp = pop2.vecteur[kj];
	pop2.vecteur[kj] = pop2.vecteur[ki];
	pop2.vecteur[ki] = temp;
	
	//Afficher_Vecteur(pop, un_probleme);
	//Afficher_Vecteur(pop2, un_probleme);

};

// Fonction Recherche Locale
T_Population Recherche_Locale(T_Probleme &un_probleme, T_Solution &sol, T_Population &pop, int iter_max) {
	int i, j,
		nc = 0,
		nb_ops = un_probleme.n * un_probleme.m,
		APP[ntotal + 1],
		fin, fin2;

	T_Solution sol2;
	T_Population pop2;
	Init_Pop(pop2);
	Init_Sol(sol2);
	Init_Sol(sol);

	Initialiser_Tableau_APP(un_probleme,APP);

	Evaluer(un_probleme, sol, pop, fin);

	i = fin;
	j = sol.PERE[i];

	while ((j != 0) && (nc <= iter_max)) {
		nc++;
		/*
		if (APP[i] == APP[j]) {
			i = j;
			j = sol.PERE[j];
		}
		else
		{
			Init_Pop(pop2);
			Init_Sol(sol2);
			sol2 = sol;
			pop2 = pop;
			Swap_Arc_Disjonctif(un_probleme, i, j, pop, pop2);
			Evaluer(un_probleme, sol2, pop2, fin2);
			if (pop2.cout < pop.cout) {
				sol = sol2;
				pop = pop2;
				fin = fin2;
				i = j;
				j = sol.PERE[i];

			}
			else
			{
				i = j;
				j = sol.PERE[j];
			}
		}
	}
		return pop;
		
		if (APP[i] != APP[j]) {

			sol2 = sol;
			pop2 = pop;
			Swap_Arc_Disjonctif(un_probleme, i, j, pop, pop2);
			Evaluer(un_probleme, sol2, pop2, fin);
			// std::cout << pop2.cout << std::endl;

			if (pop2.cout < pop.cout) {
				sol = sol2;
				pop = pop2;
				i = j;
				j = sol.PERE[i];
			}
			else
			{
				sol2 = sol;
				pop2 = pop;
				i = j;
				j = sol.PERE[j];
			}

		}
		else
		{
			i = j;
			j = sol.PERE[j];
		}
	}

	return pop;
	
}

// Fonction Tester Double
bool TesterDouble(T_Population tab_pop[], T_Population &pop)
{
	int i = 0, j = 0;
	bool egal = true;

	while (pop.cout <= tab_pop[i].cout)
	{
		if (pop.cout == tab_pop[i].cout)
		{
			j = 0;
			while (egal == true && j < card_pop)
			{
				if (pop.vecteur[j] != tab_pop[i].vecteur[j])
					egal = false;

				j++;
			}
		}
		i++;
	}
	return egal;
}

// Fonction Initialisation Population et Tableau de Population
void Init_Pop(T_Population &pop) {
	pop.cout = 0;
	for (int i = 0; i < taille_vecteur; i++) {
		pop.vecteur[i] = { 0 };
	}	
}

void Init_Tab_Pop(T_Population tab_pop[]) {
	for (int i = 0; i < card_pop; i++)
	{
		Init_Pop(tab_pop[i]);
	}
}

void Init_Sol(T_Solution &sol){
	for (int i = 0; i <= ntotal; i++) {
		sol.ES[i] = 0;
		sol.PERE[i] = 0;
	}
}
*/
/*
// Generer Population & Ajouter dans Population
void Generer_Population(T_Population tab_pop[], T_Probleme &un_probleme, int hachSigne[], int iter_max)
{
	int	compteur = 0, comptPop = 0, fin=0, nbiter = 0, n_hach;
	
	T_Solution sol1;
	T_Population pop1;

	Init_Pop(pop1);

	while (comptPop < card_pop && nbiter < iter_pop)
	{
		Generer_Vecteur(pop1, un_probleme);
		Evaluer(un_probleme, sol1, pop1, fin);
		pop1 = Recherche_Locale(un_probleme, sol1, pop1, iter_max);

		n_hach = Hachage(sol1, un_probleme);
		if (hachSigne[n_hach] == 0)
		{
			tab_pop[comptPop] = pop1;
			hachSigne[n_hach] = 1;
			comptPop++;
		}
		nbiter++;
	}
	Trier_Population(tab_pop);
	std::cout << "On a fini la Generer Population" << std::endl;
}

*/


/*
void Ajouter_dans_Population(int Tab_Sign[], T_Probleme &un_probleme, T_Population tab_pop[], T_Solution &sol1, T_Solution &sol2, T_Population &pop1, T_Population &pop2, int &nbcases) {
	
	if (Tab_Sign[Hachage(sol2, un_probleme)] == 1)
	{
		if (Tab_Sign[Hachage(sol1, un_probleme)] == 0)
		{
			tab_pop[nbcases] = pop1;
			Tab_Sign[Hachage(sol1, un_probleme)] = 1;
			nbcases++;
		}
	}
	else
	{
		tab_pop[nbcases] = pop2;
		Tab_Sign[Hachage(sol2, un_probleme)] = 1;
		nbcases++;
	}
}
*/

// Fonction Hachage
int Hachage(T_Solution &sol, T_Probleme &un_probleme)
{
	int hach = 0; // Indice dans la table de hachage
	int indice = 0;
	int prod = un_probleme.n * un_probleme.m;
	for (int i = 1; i<prod + 1; i++)               
	{
		hach += (sol.ES[i] * sol.ES[i]);
	}
	hach = hach %K;
	return(hach);
}

/*
// Fonction Trier
void Trier_Population(T_Population tab_pop[])
{
	int i;
	bool fin = 0;
	T_Population temp;

	while (!fin)
	{
		fin = 1;

		for (i = 0; i < card_pop - 1; i++)
		{
			if (tab_pop[i].cout > tab_pop[i + 1].cout)
			{
				temp = tab_pop[i + 1];
				tab_pop[i + 1] = tab_pop[i];
				tab_pop[i] = temp;
				fin = 0;
			}
		}
	}
}

// Fonction Croisement
void Croisement(T_Population &pop_fille, T_Population &pop1, T_Population &pop2, T_Probleme &un_probleme) {

	int lim, taille=(un_probleme.m*un_probleme.n), i, j = 0;
	int TAB[nmax+1] = { 0 };

	lim = (rand() % taille) + 1;

	for (i = 0; i <= lim; i++)
	{
		pop_fille.vecteur[i] = pop1.vecteur[i];
		TAB[pop_fille.vecteur[i]]++;
	}

	j = lim + 1;

	for (i = lim + 1; i <= taille; i++) {
		if (TAB[pop2.vecteur[i]] < un_probleme.m)
		{
			pop_fille.vecteur[j] = pop2.vecteur[i];
			TAB[pop2.vecteur[i]]++;
			j++;
		}
	}

	for (i = 0; i < lim; i++)
	{
		if (TAB[pop2.vecteur[i]] < un_probleme.m)
		{
			pop_fille.vecteur[j] = pop2.vecteur[i];
			TAB[pop2.vecteur[i]]++;
			j++;
		}
	}

};
*/

/*
// Fonction Mutation
void Mutation(T_Probleme &un_probleme, T_Population &pop)
{
	int a, b;
	int temp;

	a = (rand() % (un_probleme.m * un_probleme.n - 1)) + 1;
	b = rand() % a;

	temp = pop.vecteur[a];
	pop.vecteur[a] = pop.vecteur[b];
	pop.vecteur[b] = temp;
}
*/

// Algorithme Memetique

/*
void Algorithme_Memetique(T_Probleme &un_probleme, T_Population tab_pop[], int iter_max, TLineSeries *Series1)
{
	int iter = 0, pop1, pop2 = 0;
	int prod = un_probleme.n * un_probleme.m;
	int hachSigne[K] = { 0 };
	int fin = 0;

	T_Population une_population;
	T_Population pop_fille;
	T_Solution sol;

	Init_Pop(une_population);
	Generer_Population(tab_pop, un_probleme, hachSigne, iter_max);

	while (iter < iter_max)
	{

		// On prend une population parmi les meilleurs
		pop1 = rand() % (card_pop/2);
		// Puis parmi les pires
		pop2 = (rand() % (card_pop / 2)) + (card_pop / 2);

		Croisement(pop_fille, tab_pop[pop1], tab_pop[pop2], un_probleme);
		// une_population = pop_fille;
		Evaluer(un_probleme, sol, pop_fille, fin);
		std::cout << std::endl << "Makespan Fille: " << pop_fille.cout << endl;
		une_population = Recherche_Locale(un_probleme, sol, pop_fille, iter_max);
		std::cout << "Makespan Fille Apres Recherche Locale: " << une_population.cout << endl;

		// if (pop_fille.cout < une_population.cout) {
		//	une_population = pop_fille;
		// }

		if (une_population.cout < tab_pop[pop2].cout) //Si le nouveau cout est meilleur que l'ancien
		{
			if (TesterDouble(tab_pop, une_population))
			{
				tab_pop[pop2] = une_population;
				Trier_Population(tab_pop);
			}
		}

		// std::cout << tab_pop[0].cout << std::endl;
		iter++;
		// Series1->AddXY(iter, pop[0].cout);
		std::cout << iter << std::endl;
	}
}
*/

/*
// Algorithme Genetique
void Algorithme_Genetique(T_Probleme &un_probleme, T_Population tab_pop[], int iter_max, TLineSeries *Series1)
{
	int iter = 0, pop1, pop2 = 0;
	int prod = un_probleme.n * un_probleme.m;

	T_Population une_population;
	T_Population pop_fille;
	T_Solution sol;
	std::cout << "10" << std::endl;
	Init_Pop(une_population);
	std::cout << "11" << std::endl;
	// Generer_Population(tab_pop, un_probleme);
	std::cout << "122222" << std::endl;
	Trier_Population(tab_pop);
	std::cout << "12" << std::endl;
	while (iter < iter_max)
	{
		pop2 = (int)rand() % (card_pop - 12) + 12; //On prend une population parmi les 12 moins bons
		pop1 = (int)rand() % 12;				   //Puis une autre parmi les 12 meilleurs

		std::cout << "1" << std::endl;
		Croisement(pop_fille, tab_pop[pop1], tab_pop[pop2], un_probleme);

		if (iter % 10 == 0)
		{
			Mutation(un_probleme, pop_fille);
		}

		une_population = Recherche_Locale(un_probleme, sol, pop_fille, iter_max);

		std::cout << "2" << std::endl;
		if (une_population.cout < tab_pop[pop2].cout) //Si le nouveau cout est meilleur que l'ancien
		{
			if (TesterDouble(tab_pop, une_population))
			{
				tab_pop[pop2] = une_population;
				Trier_Population(tab_pop);
			}
		}

		std::cout << "3" << std::endl;
		std::cout << tab_pop[0].cout << std::endl;
		iter++;
		// Series1->AddXY(iter, pop[0].cout);
	}
}
*/