#include <string>
#include <iostream>

const int nmax = 30;
const int mmax = 30;
const int ntotal = 999;
const int taille_vecteur = nmax*mmax + 1;
const int card_pop = 60;         // Le cardinal de la population

const int iter_max_rech_loc = 10000;

const int itermax = 10000;
const int iter_pop = 20000;
const int K = 10000; // Taille du tableau de Hachage

// Définition des structures

typedef struct T_Probleme
{
	int n;
	int m;
	int Mach[nmax + 1][mmax + 1];				// Liste Machines
	int P[nmax + 1][mmax + 1];					// Liste des Processing Time
	int T[nmax + 1][mmax + 1];
	int P_inv[nmax + 1][mmax + 1];
	int T_inv[nmax + 1][mmax + 1];
}T_Probleme;

typedef struct T_Population
{
	int cout;
	int vecteur[ntotal + 1];
}T_Population;

typedef struct T_Solution
{
	int ES[ntotal + 1] = { 0 };
	int PERE[ntotal + 1] = { 0 };
}T_Solution;

void lire_instance(std::string ad_file, T_Probleme &un_probleme); // Lire le fichier
void Init_Graphe(T_Probleme &un_probleme);

void Generer_Vecteur(T_Population &pop, T_Probleme &un_probleme);
void Afficher_Vecteur(T_Population &pop, T_Probleme &un_probleme);

void Evaluer(T_Probleme &un_probleme, T_Solution &sol, T_Population &pop, int &finCheminCritique); // On remplit ES & Pere ALGO DE BIERWITH

void Initialiser_Tableau_APP(T_Probleme &un_probleme, int APP[ntotal + 1]);
void Swap_Arc_Disjonctif(T_Probleme &un_probleme, int i, int j, T_Population &pop, T_Population &pop2);

//T_Population Recherche_Locale(T_Probleme &un_probleme, T_Solution &sol, T_Population &pop, int nbMaxIterations);
T_Population Recherche_Locale(T_Probleme &Prob, T_Solution &Graph1, T_Population &Pop, int iter_max);

bool TesterDouble(T_Population tab_pop[], T_Population &pop);

// Fonction Initialisation Population et Tableau de Population
void Init_Pop(T_Population &pop);
void Init_Tab_Pop(T_Population tab_pop[]);
void Init_Sol(T_Solution &sol);

// Generer Population
void Generer_Population(T_Population tab_pop[], T_Probleme &un_probleme, int hachSigne[], int iter_max);

void Ajouter_dans_Population(int Tab_Sign[], T_Probleme &un_probleme, T_Population tab_pop[], T_Solution &sol1, T_Solution &sol2, T_Population &pop1, T_Population &pop2, int &nbcases);

// Fonction Hachage
int Hachage(T_Solution &sol, T_Probleme &un_probleme);

// Fonction Trier
void Trier_Population(T_Population tab_pop[]);

// Fonction Croisement
void Croisement(T_Population &pop_fille, T_Population &pop1, T_Population &pop2, T_Probleme &un_probleme);

// Fonction Mutation
void Mutation(T_Probleme &un_probleme, T_Population &pop);

// Algorithme Memetique
void Algorithme_Memetique(T_Probleme &un_probleme, T_Population tab_pop[], int iter_max/*, TLineSeries *Series1*/);

// Algorithme Genetique
void Algorithme_Genetique(T_Probleme &un_probleme, T_Population tab_pop[], int iter_max/*, TLineSeries *Series1*/);
