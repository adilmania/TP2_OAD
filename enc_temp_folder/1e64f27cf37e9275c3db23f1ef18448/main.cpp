// TP2_OAD.cpp : main project file.

#include "Unit_Form1.h"
#include <time.h>

// using namespace TP2_OAD;

int main(array<System::String ^> ^args)
{

	srand(time(NULL));
	int Vecteur[TAILLE_VECT] = { 3,2,1,2,3,2,3,1,1 };
//	int Vecteur3[TAILLE_VECT] = { 0 };
// int Vecteur2[TAILLE_VECT] = { 0 };
	int Makespan = 0;
	int Pere_Makespan = 0;
	// this->richTextBox1->Text = this->richTextBox1->Text + "-----------------JOBSHOP-----------------" + "\n";

	int iter_max;

	T_PROBLEME un_probleme;
	T_SOLUTION une_solution;

	std::string ad_file = "AD01.txt";

	Init_Probleme(un_probleme);
	Lecture_Fichier(ad_file, un_probleme);
//	Remplir_Probleme(un_probleme);

//	T_POPULATION Tab_Pop[CARD_POP];
//	Init_Population(Tab_Pop);
//	Generer_Population(Tab_Pop,un_probleme);

	Evaluer(Vecteur, une_solution, un_probleme, Makespan, Pere_Makespan);
	Afficher_Vecteur(Vecteur);
	std::cout << Makespan << std::endl;
	
	//Recherche_Locale(Vecteur, une_solution, un_probleme, Makespan);
	// Afficher_Vecteur(Vecteur);
	// std::cout << Makespan << std::endl;

	// this->richTextBox1->Text = this->richTextBox1->Text + Makespan + " " + Pere_Makespan  + " " "\n";

//	String^ chaine1 = this->textBox1->Text;
//	std::string SNormal1 = msclr::interop::marshal_as<std::string>(chaine1);
//	iter_max = System::Convert::ToInt32(chaine1);

//	std::string resultat;
//	std::ostringstream oss;

//	std::cout << "Entrer le NB ITER: " << std::endl;
//	std::cin >> iter_max;
//	this->richTextBox1->Text = this->richTextBox1->Text + iter_max + "\n";
//	for (int cmpt = 0; cmpt <= 100; cmpt++) {
//		Algorithme_Memetique(un_probleme, Tab_Pop, iter_max);
//		std::cout << Tab_Pop[0].Cout << std::endl;
//	}

//	this->richTextBox1->Text = this->richTextBox1->Text + "Makespan Algo Memetique: " + Tab_Pop[0].Cout + " " + "\n";

	/*
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	TP2_OAD::Unit_Form Unit_Form1;
	System::Windows::Forms::Application::Run(%Unit_Form1);
	*/

    return 0;
}
