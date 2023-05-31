#include "MyForm.h"
#include<iostream>
#include<windows.h>
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void main(array<String^>^ args) { // ^ - автоматическая отчистка памяти
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	ClientRemuteplay::MyForm form;
	Application::Run(% form);
}