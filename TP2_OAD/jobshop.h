#include <string>
#include <iostream>

const int nmax = 10;
const int mmax = 10;
const int ntotal = 40;
const int taille_vecteur = nmax*mmax + 1;

// Définition des structures

typedef struct T_PROBLEME
{
	int n;
	int m;
	int Mach[nmax + 1][mmax + 1];				// Liste Machines
	int P[nmax + 1][mmax + 1];					// Liste des Processing Time
}T_PROBLEME;

typedef struct T_SOLUS
{
	// int vecteur[ntotal + 1] = { 999, 6, 6 ,5, 5 ,6 ,5, 1, 1, 5, 3, 6, 6, 2, 4, 2, 6, 1, 3, 3, 2, 2, 5, 3, 4, 3, 3, 2, 1, 5, 4, 4, 1, 4, 1, 2, 4 };
	// int vecteur[ntotal + 1] = { 999, 3, 2, 1, 2, 3, 2, 3, 1, 1 };
	int vecteur[ntotal+1];
	int ES[ntotal + 1] = { 0 };
	int PERE[ntotal + 1] = { 0 };
}T_SOLUS;

void lire_instance(std::string ad_file, T_PROBLEME &un_probleme); // Lire le fichier
void Generer_Vecteur(T_SOLUS &SOL, T_PROBLEME &un_probleme);
void Afficher_Vecteur(T_SOLUS &SOL, T_PROBLEME &un_probleme);
void Evaluer(T_PROBLEME &un_probleme, T_SOLUS &SOL); // On remplit ES & Pere ALGO DE BIERWITH
void Recherche_Locale(T_PROBLEME &un_probleme, T_SOLUS &SOL, int nbMaxIterations);