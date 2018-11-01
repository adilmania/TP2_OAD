#include "stdafx.h"
#include "jobshop.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Fonction permettant de lire une instance � partir d'un fichier

void lire_instance(string ad_file, T_PROBLEME &un_probleme)
{
	ifstream fichier(ad_file, ios::in);  // on ouvre le fichier en lecture

	if (fichier)  // si l'ouverture a r�ussi
	{
		std::string contenu;  // d�claration d'une cha�ne qui contiendra la ligne lue
		getline(fichier, contenu);  // on met dans "contenu" la ligne

		stringstream ss(contenu);

		ss >> un_probleme.n;
		ss >> un_probleme.m;

		cout << "Nombre de Pieces: " << un_probleme.n << endl;
		cout << "Nombre de Machines: " << un_probleme.m << endl;

		cout << endl << "Affichage du fichier lu" << endl;

		int c, compteur, j;

		for (int i = 1; i <= un_probleme.n; i++)
		{
			// Lecture ligne par ligne
			getline(fichier, contenu);
			cout << contenu << endl;

			// Lecture caract�re par caract�re
			compteur = 0;
			j = 1;

			stringstream ss2(contenu);

			while (ss2 >> c)
			{
				// cout << c << endl;
				if (compteur % 2 == 0)
				{
					un_probleme.Mach[i][j] = c; /* c+1 avant */
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

void Evaluer(T_PROBLEME &un_probleme, T_SOLUS &SOL) {
	SOL.ES[0] = 0;
	int i, j, k, prec, date, mach, compteur, cour, pos, finCheminCritique;
	int prod = un_probleme.n * un_probleme.m;
	int NP[nmax] = { 0 };
	int m[mmax] = { 0 };
	int T[nmax][mmax];
	int P_inv[nmax][mmax];
	int T_inv[nmax][mmax];

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
			T[i][j] = compteur;
			compteur++;
		}
	}

	std::cout << "Affichage T" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << T[i][j] << " ";
		}
		std::cout << endl;
	}

	// Init P_INV
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			P_inv[i][un_probleme.Mach[i][j]] = un_probleme.P[i][j];
		}
	}

	std::cout << "Affichage P_INV" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << P_inv[i][j] << " ";
		}
		std::cout << endl;
	}
	
	// Init T_INV
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			T_inv[i][un_probleme.Mach[i][j]] = T[i][j];
			// std::cout << "i= " << i << " j= " << j << " " << " Mach[i][j]= " << un_probleme.Mach[i][j] << " T[i][j]= " << T[i][j] << " T_INV[i][Mach[i][j]]= " << T_inv[i][un_probleme.Mach[i][j]] << " " << std::endl;
		}
	}

	std::cout << "Affichage T_INV" << endl;
	for (i = 1; i <= un_probleme.n; i++)
	{
		for (j = 1; j <= un_probleme.m; j++)
		{
			std::cout << T_inv[i][j] << " ";
		}
		std::cout << endl;
	}

	// ALGO
	for (i = 1; i <= prod; i++)
	{
		k = SOL.vecteur[i];
		NP[k]++;

		if (NP[k] > 1) {
			prec = SOL.ES[T[k][NP[k] - 1]];
			date = prec + un_probleme.P[k][NP[k] - 1];
			if (date > SOL.ES[T[k][NP[k] - 1]])
			{
				SOL.ES[T[k][NP[k]]] = date;
				cour = T[k][NP[k]];
				pos = T[k][NP[k]-1];
				SOL.PERE[cour] = pos;
			}
		}

		mach = un_probleme.Mach[k][NP[k]];

		if (m[mach] > 0) {
			prec = SOL.ES[T_inv[m[mach]][mach]];
			if (prec + P_inv[m[mach]][mach] > SOL.ES[T[k][NP[k]]])
			{
				SOL.ES[ T[k][NP[k]] ] = prec + P_inv[m[mach]][mach];
				cour = T[k][NP[k]];
				pos = T_inv[m[mach]][mach];
				SOL.PERE[cour] = pos;
			}
		}
		m[mach] = k;
		cout << "Passage dans la boucle" << endl;

	}

	for (i = 1; i <= un_probleme.n; i++) {
		if (SOL.ES[0]<SOL.ES[i*un_probleme.m]+un_probleme.P[i][un_probleme.m]) {
			SOL.ES[0] = SOL.ES[i*un_probleme.m] + un_probleme.P[i][un_probleme.m]; /* Calcul du Makespan */
			finCheminCritique = i*un_probleme.m;
		}
	}

	cout << endl << "Affichage du makespan" << endl;
	cout << SOL.ES[0] << endl;

	cout << "Affichage du chemin critique" << endl;
	i = SOL.PERE[finCheminCritique]; /* PK 24 AVANT? */
	while (i != 0) {
		cout << i << " ";
		i = SOL.PERE[i];
	}

	cout << "R�ussi" << endl;
}
