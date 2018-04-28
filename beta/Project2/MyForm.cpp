#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project2::MyForm form;
	Application::Run(%form);
}

System::Void Project2::MyForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog1->Title = L"§£§í§Ò§Ö§â§Ú§ä§Ö §æ§Ñ§Û§Ý §Õ§Ý§ñ §â§Ö§ê§Ö§ß§Ú§ñ";
	openFileDialog1->ShowDialog();
	if (openFileDialog1->CheckFileExists) {
		System::String^ S_path = openFileDialog1->FileName;
		char* path = new char[S_path->Length];
		for (__int64 i = 0; i < S_path->Length; ++i) {
			path[i] = (char)S_path[i];
		}
		solve(path);
	}
	else {
		MessageBox::Show("§¶§Ñ§Û§Ý §ß§Ö §Ó§í§Ò§â§Ñ§ß §Ú§Ý§Ú §ß§Ö §ã§å§ë§Ö§ã§ä§Ó§å§Ö§ä.");
	}
	return System::Void();
}
