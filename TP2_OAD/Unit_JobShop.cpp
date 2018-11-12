#include "stdafx.h"
#include "Unit_JobShop.h"

using namespace std;

void Lecture_Fichier(std::string ad_file, T_PROBLEME &un_probleme /*MEMO*/) {
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
					un_probleme.Mach[i][j] = c + 1; /* c+1 avant */
				}
				else
				{
					un_probleme.P_Time[i][j] = c;
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

void Init_Probleme(T_PROBLEME &un_probleme) {
	int i, j;
	un_probleme.n = 0;
	un_probleme.m = 0;

	for (i = 0; i <= N_MAX; i++)
	{
		for (j = 0; j <= M_MAX; j++) {
			un_probleme.Mach[i][j] = 0;
		}
			
	}

	for (i = 0; i <= N_MAX; i++)
	{
		for (j = 0; j <= M_MAX; j++) {
			un_probleme.P_Time[i][j] = 0;
		}
	}

	for (i = 0; i <= N_MAX; i++)
	{
		for (j = 0; j <= M_MAX; j++) {
			un_probleme.P_INV[i][j] = 0;
		}

	}

	for (i = 0; i <= N_MAX; i++)
	{
		for (j = 0; j <= M_MAX; j++) {
			un_probleme.T[i][j] = 0;
		}
	}

	for (i = 0; i <= N_MAX; i++)
	{
		for (j = 0; j <= M_MAX; j++) {
			un_probleme.T_INV[i][j] = 0;
		}
	}
}

void Remplir_Probleme(T_PROBLEME &un_probleme) {

	int i, j, compteur;

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

	// Init P_INV
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			un_probleme.P_INV[i][un_probleme.Mach[i][j]] = un_probleme.P_Time[i][j];
		}
	}

	// Init T_INV
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			un_probleme.T_INV[i][un_probleme.Mach[i][j]] = un_probleme.T[i][j];
		}
	}

}

void Init_Solution(T_PROBLEME &un_probleme, T_SOLUTION &une_solution) {
	int i, NbOp = un_probleme.n * un_probleme.m;

	for (i = 0; i < NbOp; i++) {
		une_solution.PERE[i] = 0;
		une_solution.ES[i] = 0;
	}
}

void Init_Individu(T_POPULATION &un_individu) {
	int i;
	un_individu.Cout = 0;

	for (i = 0; i < TAILLE_VECT; i++) {
		un_individu.Vecteur[i] = 0;
	}

}

void Init_Population(T_POPULATION Tab_Pop[CARD_POP]) {
	int i, j;

	for (i = 0; i < CARD_POP; i++) {
		for (j = 0; j < CARD_POP; j++) {
			Tab_Pop[i].Vecteur[j] = 0;
		}
		Tab_Pop[i].Cout = 0;
	}
}

void Evaluer(int Vecteur[TAILLE_VECT], T_SOLUTION &une_solution, T_PROBLEME &un_probleme, int &Makespan, int &Pere_Makespan) {

	Makespan = 0;
	int i, k, prec, date, mach, cour, pos;
	int NbOp = un_probleme.n * un_probleme.m;
	int NP[N_MAX] = { 0 };
	int m[M_MAX] = { 0 };

	Init_Solution(un_probleme, une_solution);

	// ALGO
	for (i = 1; i <= NbOp; i++)
	{
		k = Vecteur[i];
		NP[k]++;

		if (NP[k] > 1) {
			prec = une_solution.ES[un_probleme.T[k][NP[k] - 1]];
			date = prec + un_probleme.P_Time[k][NP[k] - 1];
			if (date > une_solution.ES[un_probleme.T[k][NP[k] - 1]])
			{
				une_solution.ES[un_probleme.T[k][NP[k]]] = date;
				cour = un_probleme.T[k][NP[k]];
				pos = un_probleme.T[k][NP[k] - 1];
				une_solution.PERE[cour] = pos;
			}
		}

		mach = un_probleme.Mach[k][NP[k]];

		if (m[mach] > 0) {
			prec = une_solution.ES[un_probleme.T_INV[m[mach]][mach]];
			if (prec + un_probleme.P_INV[m[mach]][mach] > une_solution.ES[un_probleme.T[k][NP[k]]])
			{
				une_solution.ES[un_probleme.T[k][NP[k]]] = prec + un_probleme.P_INV[m[mach]][mach];
				cour = un_probleme.T[k][NP[k]];
				pos = un_probleme.T_INV[m[mach]][mach];
				une_solution.PERE[cour] = pos;
			}
		}
		m[mach] = k;
	}

	// Calcul du cout (makespan)
	for (i = 1; i <= un_probleme.n; i++) {
		if (Makespan<une_solution.ES[i*un_probleme.m] + un_probleme.P_Time[i][un_probleme.m]) {
			Makespan = une_solution.ES[i*un_probleme.m] + un_probleme.P_Time[i][un_probleme.m];
			Pere_Makespan = i*un_probleme.m;
		}
	}

}