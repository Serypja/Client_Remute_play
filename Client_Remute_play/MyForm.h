#pragma once
#include<windows.h>
#include<iostream>
//#include <winsock2.h>
#using <System.dll>
#include <list>

using namespace System::Text;
using namespace System::Collections::Generic;

using namespace System::Windows::Forms;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Threading::Tasks;

namespace ClientRemuteplay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label1;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(194, 84);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Подключиться UDP";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(358, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(418, 375);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 331);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(788, 399);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {


			// Создание объекта UdpClient для прослушивания входящих пакетов
			UdpClient^ client = gcnew UdpClient(8884);
			IPAddress^ serverAddress = IPAddress::Parse("192.168.0.149");
			IPEndPoint^ endPoint = gcnew IPEndPoint(serverAddress, 8884);
			int maxPacketSize = 65507; // максимальный размер пакета UDP

			// Создание буфера для хранения принятых данных
			List<Byte>^ receivedData = gcnew List<Byte>();
			

			// Прием пакетов и добавление данных в буфер
			while (true)
			{
				array<Byte>^ packetData = client->Receive(endPoint);
				receivedData->AddRange(packetData);

				// Если приняты все пакеты, выход из цикла
				if (packetData->Length < maxPacketSize)
					break;
			}

			// Преобразование списка байтов в массив байтов
			array<Byte>^ pngData = receivedData->ToArray();

			// Сохранение принятых данных в файл
			System::IO::File::WriteAllBytes("image.png", pngData);

			
			
		
		}
	};
}

//______________________________________________Передача картинки до 64 МБ
//// Создаем UDP сервер
//UdpClient^ server = gcnew UdpClient(8884);

//// Получаем адрес и порт отправителя
//IPEndPoint^ ipaddres_poluch = gcnew IPEndPoint(IPAddress::Any, 0);

//// Принимаем данные от клиента
//array<Byte>^ data = server->Receive(ipaddres_poluch);

//
//// Сохраняем принятые данные в файл
//System::IO::File::WriteAllBytes("image.png", data);

//// Закрываем сервер
//server->Close();