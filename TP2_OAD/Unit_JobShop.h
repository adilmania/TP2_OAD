#ifndef UNIT_JOBSHOPH
#define UNIT_JOBSHOPH

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#define CARD_POP 60
#define K_HACH 10000
#define ITER_POP 20000

// Variables constantes
const int N_MAX = 40;
const int M_MAX = 40;
const int TAILLE_VECT = (N_MAX * M_MAX) + 1;
const int ITER_MAX = 10000;

typedef struct T_PROBLEME {
	int n;
	int m;
	int P_Time[N_MAX + 1][M_MAX + 1];
	int Mach[N_MAX + 1][M_MAX + 1];
}T_PROBLEME;

typedef struct T_POPULATION {
	int Cout;
	int Vecteur[TAILLE_VECT];
}T_POPULATION;

typedef struct T_SOLUTION {
	int ES[TAILLE_VECT + 1];
	int PERE[TAILLE_VECT + 1];
}T_SOLUTION;

void Lecture_Fichier(std::string ad_file, T_PROBLEME &un_probleme);
void Init_Probleme(T_PROBLEME &un_probleme);

void Init_Solution(T_PROBLEME &un_probleme, T_SOLUTION &une_solution);
void Init_Individu(T_POPULATION &un_individu);
void Init_Population(T_POPULATION Tab_Pop[CARD_POP]);

void Evaluer(int Vecteur[TAILLE_VECT], T_SOLUTION &une_solution, T_PROBLEME &un_probleme, int &Makespan, int &Pere_Makespan);
void Generer_Bierwith(int Vecteur[TAILLE_VECT], T_PROBLEME &un_probleme);
void Generer_Population(T_POPULATION Tab_Pop[CARD_POP], T_PROBLEME &un_probleme);
void Afficher_Vecteur(int Vecteur[TAILLE_VECT]);

T_POPULATION Recherche_Locale(int Vecteur1[TAILLE_VECT], T_SOLUTION &une_solution1, T_PROBLEME &un_probleme, int &Makespan1);
void Swap_Arc_Disjonctif(T_PROBLEME &un_probleme, int Vecteur1[TAILLE_VECT], int Vecteur2[TAILLE_VECT], int Ind1, int Ind2, int NumP1, int NumP2);

int Hachage(T_SOLUTION &une_solution, T_PROBLEME &un_probleme);

void Trier_Population(T_POPULATION Tab_Pop[CARD_POP]);
void Croisement(int VECTEUR_FILS[TAILLE_VECT], int Vecteur1[TAILLE_VECT], int Vecteur2[TAILLE_VECT], T_PROBLEME &un_probleme);
void Mutation(T_PROBLEME &un_probleme, int Vecteur[TAILLE_VECT]);
int TesterDouble(T_POPULATION Tab_Pop[CARD_POP], T_POPULATION &une_population);

void Algorithme_Memetique(T_PROBLEME &un_probleme, T_POPULATION Tab_Pop[CARD_POP], int iter_max, System::Windows::Forms::DataVisualization::Charting::Chart^  chart1);
void Algorithme_Genetique(T_PROBLEME &un_probleme, T_POPULATION Tab_Pop[CARD_POP], int iter_max, System::Windows::Forms::DataVisualization::Charting::Chart^  chart1);

#endif // !UNIT_JOBSHOPH

