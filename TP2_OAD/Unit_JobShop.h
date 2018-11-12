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
	int T[N_MAX + 1][M_MAX + 1];
	int P_INV[N_MAX + 1][M_MAX + 1];
	int T_INV[N_MAX + 1][M_MAX + 1];
}T_PROBLEME;

typedef struct T_POPULATION {
	int Cout;
	int Vecteur[TAILLE_VECT];
}T_POPULATION;

typedef struct T_SOLUTION {
	int ES[TAILLE_VECT + 1];
	int PERE[TAILLE_VECT + 1];
}T_SOLUTION;

void Lecture_Fichier(std::string ad_file, T_PROBLEME &un_probleme /*MEMO*/);
void Init_Probleme(T_PROBLEME &un_probleme);
void Remplir_Probleme(T_PROBLEME &un_probleme);
// Fonction Print dans le Memo
void Init_Solution(T_PROBLEME &un_probleme, T_SOLUTION &une_solution);
void Init_Individu(T_POPULATION &un_individu);
void Init_Population(T_POPULATION Tab_Pop[CARD_POP]);
// Fonction Print Prob dans le Memo
// Fonction Print Pop dans le Memo

// EVALUER
void Evaluer(int Vecteur[TAILLE_VECT], T_SOLUTION &une_solution, T_PROBLEME &un_probleme, int &Makespan, int &Pere_Makespan);

#endif // !UNIT_JOBSHOPH

