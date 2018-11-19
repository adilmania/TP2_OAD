#pragma once

#ifndef UNITFORM1
#define UNITFORM1

#include "Unit_JobShop.h"
#include <string.h>
#include <sstream>
#include <msclr/marshal_cppstd.h>

namespace TP2_OAD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Unit_Form
	/// </summary>
	public ref class Unit_Form : public System::Windows::Forms::Form
	{
	public:
		Unit_Form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Unit_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(67, 154);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(291, 83);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Executer";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Unit_Form::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(637, 53);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(668, 274);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(67, 102);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(532, 31);
			this->textBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(62, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(203, 25);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Nombre d\'Itérations:";
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(67, 366);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(1238, 484);
			this->chart1->TabIndex = 4;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Unit_Form::chart1_Click);
			// 
			// Unit_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1358, 891);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Unit_Form";
			this->Text = L"JobShop";
			this->Load += gcnew System::EventHandler(this, &Unit_Form::Unit_Form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		this->richTextBox1->Text = this->richTextBox1->Text + "-----------------JOBSHOP-----------------" + "\n";

		int iter_max;

		T_PROBLEME un_probleme;
		T_SOLUTION une_solution;

		std::string ad_file = "LA01.txt";

		Init_Solution(un_probleme, une_solution);
		Init_Probleme(un_probleme);
		Lecture_Fichier(ad_file, un_probleme);
//		Generer_Bierwith(Vecteur, un_probleme);
		T_POPULATION Tab_Pop[CARD_POP];
		Init_Population(Tab_Pop);

//		Evaluer(Vecteur, une_solution, un_probleme, Makespan, Pere_Makespan);
//		this->richTextBox1->Text = this->richTextBox1->Text + Makespan + " " + Pere_Makespan  + " " "\n";

		String^ chaine1 = this->textBox1->Text;
		std::string SNormal1 = msclr::interop::marshal_as<std::string>(chaine1);
		iter_max = System::Convert::ToInt32(chaine1);

		std::string resultat;
		std::ostringstream oss;

		std::cin >> iter_max;
		this->richTextBox1->Text = this->richTextBox1->Text + iter_max + "\n";
		Algorithme_Memetique(un_probleme, Tab_Pop, iter_max);
		this->richTextBox1->Text = this->richTextBox1->Text + "Makespan Algo Memetique: " + Tab_Pop[0].Cout + " " + "\n";
//		Algorithme_Genetique(un_probleme, Tab_Pop, iter_max);
//		this->richTextBox1->Text = this->richTextBox1->Text + "Makespan Algo Genetique: " + Tab_Pop[0].Cout + " " + "\n";
		

		//this->chart1->Series->Add("Series2");
		//this->chart1->Series["Series2"]->Points->AddXY(20);
		//this->chart1->Series["Series2"]->ChartArea = "ChartArea1";
		
		//chart1->Series[name]->Points->AddXY(x[i], y[i]);
		
		//this->chart1->AddXY(Nbiter, Tab_Pop[0].Cout);
		//Series2->AddXY(NbIter, Pop[0].Cout);
	}

	private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void Unit_Form_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}

#endif
