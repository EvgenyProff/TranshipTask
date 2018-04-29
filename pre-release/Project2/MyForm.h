#pragma once
#ifndef __MYFORM__
#define __MYFORM__

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// §³§Ó§à§Õ§Ü§Ñ §Õ§Ý§ñ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: §Õ§à§Ò§Ñ§Ó§î§ä§Ö §Ü§à§Õ §Ü§à§ß§ã§ä§â§å§Ü§ä§à§â§Ñ
			//
		}

	protected:
		/// <summary>
		/// §°§ã§Ó§à§Ò§à§Õ§Ú§ä§î §Ó§ã§Ö §Ú§ã§á§à§Ý§î§Ù§å§Ö§Þ§í§Ö §â§Ö§ã§å§â§ã§í.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:

	private:
		/// <summary>
		/// §°§Ò§ñ§Ù§Ñ§ä§Ö§Ý§î§ß§Ñ§ñ §á§Ö§â§Ö§Þ§Ö§ß§ß§Ñ§ñ §Ü§à§ß§ã§ä§â§å§Ü§ä§à§â§Ñ.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// §´§â§Ö§Ò§å§Ö§Þ§í§Û §Þ§Ö§ä§à§Õ §Õ§Ý§ñ §á§à§Õ§Õ§Ö§â§Ø§Ü§Ú §Ü§à§ß§ã§ä§â§å§Ü§ä§à§â§Ñ ¡ª §ß§Ö §Ú§Ù§Þ§Ö§ß§ñ§Û§ä§Ö 
		/// §ã§à§Õ§Ö§â§Ø§Ú§Þ§à§Ö §ï§ä§à§Ô§à §Þ§Ö§ä§à§Õ§Ñ §ã §á§à§Þ§à§ë§î§ð §â§Ö§Õ§Ñ§Ü§ä§à§â§Ñ §Ü§à§Õ§Ñ.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LavenderBlush;
			this->button1->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(12, 487);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(337, 45);
			this->button1->TabIndex = 0;
			this->button1->Text = L"§£§í§Ò§â§Ñ§ä§î §æ§Ñ§Û§Ý";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::LavenderBlush;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::Color::Black;
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(752, 467);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = resources->GetString(L"textBox1.Text");
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::GhostWhite;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(778, 544);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
void solve(char path[]);
#endif