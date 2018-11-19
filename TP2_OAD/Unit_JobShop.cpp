#include "stdafx.h"
#include "Unit_JobShop.h"

void Lecture_Fichier(std::string ad_file, T_PROBLEME &un_probleme) {
	std::ifstream fichier(ad_file, std::ios::in);  // on ouvre le fichier en lecture

	if (fichier)  // si l'ouverture a réussi
	{
		std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
		getline(fichier, contenu);  // on met dans "contenu" la ligne

		std::stringstream ss(contenu);

		ss >> un_probleme.n;
		ss >> un_probleme.m;

		int c, compteur, j;

		for (int i = 1; i <= un_probleme.n; i++)
		{
			// Lecture ligne par ligne
			getline(fichier, contenu);

			// Lecture caractère par caractère
			compteur = 0;
			j = 1;

			std::stringstream ss2(contenu);

			while (ss2 >> c)
			{

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
		std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
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
		une_solution.ES[0] = 0;
		int i, j, k, prec, date, mach, compteur, cour, pos, finCheminCritique;
		int prod = un_probleme.n * un_probleme.m;
		int NP[N_MAX] = { 0 };
		int m[M_MAX] = { 0 };
		int T[N_MAX][M_MAX];
		int P_inv[N_MAX][M_MAX];
		int T_inv[N_MAX][M_MAX];

		Init_Solution(un_probleme, une_solution);

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

		// Init P_INV
		for (i = 1; i <= un_probleme.n; i++)
		{
			for (j = 1; j <= un_probleme.m; j++)
			{
				P_inv[i][un_probleme.Mach[i][j]] = un_probleme.P_Time[i][j];
			}
		}

		// Init T_INV
		for (i = 1; i <= un_probleme.n; i++)
		{
			for (j = 1; j <= un_probleme.m; j++)
			{
				T_inv[i][un_probleme.Mach[i][j]] = T[i][j];
			}
		}
		
		// ALGO
		for (i = 1; i <= prod; i++)
		{

			k = Vecteur[i];
			NP[k]++;
			if (NP[k] > 1) {
				prec = une_solution.ES[T[k][NP[k] - 1]];
				date = prec + un_probleme.P_Time[k][NP[k] - 1];
				if (date > une_solution.ES[T[k][NP[k] - 1]])
				{
					une_solution.ES[T[k][NP[k]]] = date;
					cour = T[k][NP[k]];
					pos = T[k][NP[k] - 1];
					une_solution.PERE[cour] = pos;
				}
			}
			mach = un_probleme.Mach[k][NP[k]];
			if (m[mach] > 0) {
				prec = une_solution.ES[T_inv[m[mach]][mach]];
				if (prec + P_inv[m[mach]][mach] > une_solution.ES[T[k][NP[k]]])
				{
					une_solution.ES[T[k][NP[k]]] = prec + P_inv[m[mach]][mach];
					cour = T[k][NP[k]];
					pos = T_inv[m[mach]][mach];
					une_solution.PERE[cour] = pos;
				}
			}
			m[mach] = k;
		}
		for (i = 1; i <= un_probleme.n; i++) {
			if (une_solution.ES[0]<une_solution.ES[i*un_probleme.m] + un_probleme.P_Time[i][un_probleme.m]) {
				une_solution.ES[0] = une_solution.ES[i*un_probleme.m] + un_probleme.P_Time[i][un_probleme.m]; /* Calcul du Makespan */
				finCheminCritique = i*un_probleme.m;
			}
		}
		Makespan = une_solution.ES[0];
		Pere_Makespan = finCheminCritique;
	}

void Generer_Bierwith(int Vecteur[TAILLE_VECT], T_PROBLEME &un_probleme) {
	int i;
	int tab[TAILLE_VECT] = { 0 };
	int NbOp = un_probleme.n * un_probleme.m;

	Vecteur[0] = 999;

	for (i = 1; i <= NbOp; i++)
	{
		do
		{
			Vecteur[i] = (int)(rand() % un_probleme.n) + 1;
		} while (tab[Vecteur[i]] >= (un_probleme.m));

		tab[Vecteur[i]]++;

	}
}

void Generer_Population(T_POPULATION Tab_Pop[CARD_POP], T_PROBLEME &un_probleme) {

	int i, NbIter = 0, Cpt = 0, Tab[K_HACH] = { 0 }, Makespan = 0, Pere_Makespan = 0;

	T_SOLUTION Sol1, Sol2;
	int NbOp = un_probleme.n * un_probleme.m;
	T_POPULATION Indiv1, Indiv2;

	while (Cpt < CARD_POP && NbIter < ITER_POP)
	{
		Init_Solution(un_probleme, Sol1);
		Init_Solution(un_probleme, Sol2);
		Init_Individu(Indiv1);
		Init_Individu(Indiv2);

		Generer_Bierwith(Indiv1.Vecteur, un_probleme);
		Evaluer(Indiv1.Vecteur, Sol1, un_probleme, Makespan, Pere_Makespan);

		Indiv1.Cout = Makespan;

		for (i = 0; i <= NbOp; i++)
		{
			Indiv2.Vecteur[i] = Indiv1.Vecteur[i];
		}

		Indiv1 = Recherche_Locale(Indiv2.Vecteur, Sol2, un_probleme, Makespan);

		Indiv2.Cout = Makespan;

		if (Tab[Hachage(Sol2, un_probleme)] == 1)
		{
			if (Tab[Hachage(Sol1, un_probleme)] == 0)
			{
				Tab_Pop[Cpt] = Indiv1;
				Tab[Hachage(Sol1, un_probleme)] = 1;
				Cpt++;
			}
		}
		else
		{
			Tab_Pop[Cpt] = Indiv2;
			Tab[Hachage(Sol2, un_probleme)] = 1;
			Cpt++;
		}
		NbIter++;
	}
	Trier_Population(Tab_Pop);
}

void Afficher_Vecteur(int Vecteur[TAILLE_VECT]) {
	int i;
	int nb_operations = 55;
	printf("Vecteur de Bierwith : ");
	for (i = 0; i < nb_operations + 1; i++) {
		printf("%d ", Vecteur[i]);
	}
	printf("\n");
}

T_POPULATION Recherche_Locale(int Vecteur1[TAILLE_VECT], T_SOLUTION &une_solution1, T_PROBLEME &un_probleme, int &Makespan1) {

	int NbOp, i, Ind1, Ind2, NbIter = 0, Vecteur2[TAILLE_VECT] = { 0 }, Int1, Int2;
	T_SOLUTION une_solution2;
	T_POPULATION une_population;
	Init_Individu(une_population);

	int Makespan2 = 0, Pere_Makespan1 = 0, Pere_Makespan2 = 0;

	NbOp = un_probleme.n * un_probleme.m;
	Evaluer(Vecteur1, une_solution1, un_probleme, Makespan1, Pere_Makespan1);

	Ind1 = Pere_Makespan1;
	Ind2 = une_solution1.PERE[Ind1];

	while ((Ind2 != 0) && (NbIter < ITER_MAX))
	{
		Int1 = ((Ind1 - 1) / un_probleme.m) + 1;
		Int2 = ((Ind2 - 1) / un_probleme.m) + 1;

		if (Int1 == Int2)
		{
			Ind1 = Ind2;
			Ind2 = une_solution1.PERE[Ind2];
		}
		else
		{
			Swap_Arc_Disjonctif(un_probleme, Vecteur1, Vecteur2, Ind1, Ind2, Int1, Int2);
			Evaluer(Vecteur2, une_solution2, un_probleme, Makespan2, Pere_Makespan2);

			if (Makespan2 < Makespan1)
			{
				for (i = 0; i < (NbOp + 1); i++)
				{
					une_solution1.PERE[i] = une_solution2.PERE[i];
					une_solution1.ES[i] = une_solution2.ES[i];
					Vecteur1[i] = Vecteur2[i];
				}
				Pere_Makespan1 = Pere_Makespan2;
				Makespan1 = Makespan2;
			}
			Ind1 = Ind2;
			Ind2 = une_solution1.PERE[Ind1];
		}
		NbIter++;
	}
	une_population.Cout = Makespan1;

	for (i = 0; i <= NbOp; i++)
	{
		une_population.Vecteur[i] = Vecteur1[i];
	}

	return une_population;
}

void Swap_Arc_Disjonctif(T_PROBLEME &un_probleme, int Vecteur1[TAILLE_VECT], int Vecteur2[TAILLE_VECT], int Ind1, int Ind2, int NumP1, int NumP2) {
	int NbOp, Tmp, k = 1, Ind1P, Ind2P, Pos1, Pos2, Cpt1 = 0, Cpt2 = 0;

	Ind1P = ((Ind1 - 1) % un_probleme.m) + 1;
	Ind2P = ((Ind2 - 1) % un_probleme.m) + 1;

	NbOp = un_probleme.n * un_probleme.m;

	for (k = 0; k < NbOp + 1; k++)
	{
		Vecteur2[k] = Vecteur1[k]; 
	}

	if (Ind1P != 0 && Ind2P != 0) {
		k = 1;
		while (Cpt1 != Ind1P && k <= NbOp)
		{
			if (Vecteur2[k] == NumP1)
			{
				Cpt1++;
			}
			k++;
		}

		Pos1 = k - 1;
		k = 1;

		while (Cpt2 != Ind2P && k <= NbOp)
		{
			if (Vecteur2[k] == NumP2)
			{
				Cpt2++;
			}
			k++;
		}
		Pos2 = k - 1;

		Tmp = Vecteur2[Pos1];
		Vecteur2[Pos1] = Vecteur2[Pos2];
		Vecteur2[Pos2] = Tmp;
	}

}

int Hachage(T_SOLUTION &une_solution, T_PROBLEME &un_probleme) {
	int hach = 0; // Indice dans la table de hachage
	int indice = 0;
	int NbOp = un_probleme.n * un_probleme.m;
	for (int i = 1; i<NbOp + 1; i++)
	{
		hach += (une_solution.ES[i] * une_solution.ES[i]);
	}
	hach = hach % K_HACH;
	return(hach);
}

void Trier_Population(T_POPULATION Tab_Pop[CARD_POP]) {
	int i;
	bool fin = 0;
	T_POPULATION temp;

	while (!fin)
	{
		fin = 1;

		for (i = 0; i < CARD_POP - 1; i++)
		{
			if (Tab_Pop[i].Cout > Tab_Pop[i + 1].Cout)
			{
				temp = Tab_Pop[i + 1];
				Tab_Pop[i + 1] = Tab_Pop[i];
				Tab_Pop[i] = temp;
				fin = 0;
			}
		}
	}
}

void Croisement(int VECTEUR_FILS[TAILLE_VECT], int Vecteur1[TAILLE_VECT], int Vecteur2[TAILLE_VECT], T_PROBLEME &un_probleme) {
	
	int lim, NbOp = (un_probleme.m*un_probleme.n), i, j = 1; // j commence pas de 0
	int TAB[N_MAX + 1] = { 0 };

	lim = (rand() % NbOp) + 1;
	
	for (i = 0; i <= lim; i++)
	{
		VECTEUR_FILS[i] = Vecteur1[i];
		TAB[VECTEUR_FILS[i]]++;
	}

	j = lim + 1;

	for (i = lim + 1; i <= NbOp; i++) {
		if (TAB[Vecteur2[i]] < un_probleme.m)
		{
			VECTEUR_FILS[j] = Vecteur2[i];
			TAB[Vecteur2[i]]++;
			j++;
		}
	}

	for (i = 1; i <= lim; i++)
	{
		if (TAB[Vecteur2[i]] < un_probleme.m && j <= NbOp)
		{
			VECTEUR_FILS[j] = Vecteur2[i];
			TAB[Vecteur2[i]]++;
			j++;
		}
	}
	
}

void Mutation(T_PROBLEME &un_probleme, int Vecteur[TAILLE_VECT]) {
	int a, b;
	int temp;

	a = (rand() % (un_probleme.m * un_probleme.n - 1)) + 1;
	b = rand() % a + 1;

	temp = Vecteur[a];
	Vecteur[a] = Vecteur[b];
	Vecteur[b] = temp;
}

int TesterDouble(T_POPULATION Tab_Pop[CARD_POP], T_POPULATION &une_population) {

	int i = 0, j;
	int Res = 1;

	while (une_population.Cout <= Tab_Pop[i].Cout)
	{
		if (une_population.Cout == Tab_Pop[i].Cout)
		{
			j = 1;
			while (Res == 1 && j < CARD_POP)
			{
				if (une_population.Vecteur[j] != Tab_Pop[i].Vecteur[j])
				{
					Res = 0;
				}
				j++;
			}
		}
		i++;
	}

	return Res;

}

void Algorithme_Memetique(T_PROBLEME &un_probleme, T_POPULATION Tab_Pop[CARD_POP], int iter_max, System::Windows::Forms::DataVisualization::Charting::Chart^  chart1) {
	int NbIter = 0, Indiv1, Indiv2 = 0, Vecteur[TAILLE_VECT];
	int Makespan = 0, Pere_Makespan = 0;

	T_POPULATION une_population;
	T_SOLUTION une_solution;
	Init_Individu(une_population);

	Generer_Population(Tab_Pop, un_probleme);
	Trier_Population(Tab_Pop);

	while (NbIter < iter_max)
	{
		// On prend une population parmi les meilleurs
		Indiv1 = rand() % (CARD_POP / 2);
		// Puis parmi les pires
		Indiv2 = (rand() % (CARD_POP / 2)) + (CARD_POP / 2);

		Croisement(Vecteur, Tab_Pop[Indiv1].Vecteur, Tab_Pop[Indiv2].Vecteur, un_probleme);

		Evaluer(Vecteur, une_solution, un_probleme, Makespan, Pere_Makespan);

		une_population = Recherche_Locale(Vecteur, une_solution, un_probleme, Makespan);

		if (une_population.Cout < Tab_Pop[Indiv2].Cout)
		{
			if (TesterDouble(Tab_Pop, une_population))
			{
				Tab_Pop[Indiv2] = une_population;
				Trier_Population(Tab_Pop);
			}
		}

		chart1->Series["Algo Memetique"]->Points->AddXY(NbIter, Tab_Pop[0].Cout);
		//Series1->AddXY(NbIter, Tab_Pop[0].Cout);
		NbIter++;
	}

}

void Algorithme_Genetique(T_PROBLEME &un_probleme, T_POPULATION Tab_Pop[CARD_POP], int iter_max, System::Windows::Forms::DataVisualization::Charting::Chart^  chart1) {
	int NbIter = 0, Indiv1, Indiv2 = 0, Vecteur[TAILLE_VECT];
	int Makespan = 0, Pere_Makespan = 0;

	T_POPULATION une_population;
	T_SOLUTION une_solution;
	Init_Individu(une_population);

	Generer_Population(Tab_Pop, un_probleme);
	Trier_Population(Tab_Pop);

	while (NbIter < iter_max)
	{
		// On prend une population parmi les meilleurs
		Indiv1 = rand() % (CARD_POP / 2);
		// Puis parmi les pires
		Indiv2 = (rand() % (CARD_POP / 2)) + (CARD_POP / 2);

		Croisement(Vecteur, Tab_Pop[Indiv1].Vecteur, Tab_Pop[Indiv2].Vecteur, un_probleme);

		if (NbIter % 10 == 0){
			Mutation(un_probleme, Vecteur);
		}
			
		Evaluer(Vecteur, une_solution, un_probleme, Makespan, Pere_Makespan);
		une_population = Recherche_Locale(Vecteur, une_solution, un_probleme, Makespan);

		if (une_population.Cout < Tab_Pop[Indiv2].Cout)
		{
			if (TesterDouble(Tab_Pop, une_population))
			{
				Tab_Pop[Indiv2] = une_population;
				Trier_Population(Tab_Pop);
			}
		}

		chart1->Series["Algo Genetique"]->Points->AddXY(NbIter, Tab_Pop[0].Cout);
		NbIter++;
	}

}