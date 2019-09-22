#pragma once
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "GraphicExtensions.h"

namespace Brez {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public enum State {
		LineDraw, СircleDraw, EllipseDraw
	};

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	private:
		int x1, x2, y1, y2;
		State state;
		bool mousedown;
		List<Line^>^ lines;
		List<Circle^>^ circles;
		List<Ellipse^>^ ellipses;


	public:
		//Конструктор
		MyForm(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm();

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  редактироватьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  отрезкиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  окружностиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  эллипсыToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  очиститьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->редактироватьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->отрезкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->окружностиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->эллипсыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->очиститьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->редактироватьToolStripMenuItem,
					this->оПрограммеToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1010, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// редактироватьToolStripMenuItem
			// 
			this->редактироватьToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->отрезкиToolStripMenuItem,
					this->окружностиToolStripMenuItem, this->эллипсыToolStripMenuItem, this->toolStripSeparator1, this->очиститьToolStripMenuItem
			});
			this->редактироватьToolStripMenuItem->Name = L"редактироватьToolStripMenuItem";
			this->редактироватьToolStripMenuItem->Size = System::Drawing::Size(99, 20);
			this->редактироватьToolStripMenuItem->Text = L"Редактировать";
			// 
			// отрезкиToolStripMenuItem
			// 
			this->отрезкиToolStripMenuItem->Name = L"отрезкиToolStripMenuItem";
			this->отрезкиToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->отрезкиToolStripMenuItem->Text = L"Отрезки";
			this->отрезкиToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::отрезкиToolStripMenuItem_Click);
			// 
			// окружностиToolStripMenuItem
			// 
			this->окружностиToolStripMenuItem->Name = L"окружностиToolStripMenuItem";
			this->окружностиToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->окружностиToolStripMenuItem->Text = L"Окружности";
			this->окружностиToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::окружностиToolStripMenuItem_Click);
			// 
			// эллипсыToolStripMenuItem
			// 
			this->эллипсыToolStripMenuItem->Name = L"эллипсыToolStripMenuItem";
			this->эллипсыToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->эллипсыToolStripMenuItem->Text = L"Эллипсы";
			this->эллипсыToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::эллипсыToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(140, 6);
			// 
			// очиститьToolStripMenuItem
			// 
			this->очиститьToolStripMenuItem->Name = L"очиститьToolStripMenuItem";
			this->очиститьToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->очиститьToolStripMenuItem->Text = L"Очистить";
			this->очиститьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::очиститьToolStripMenuItem_Click);
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::оПрограммеToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox1->Location = System::Drawing::Point(0, 57);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(500, 429);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox2->Location = System::Drawing::Point(506, 57);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(500, 429);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox2_Paint);
			this->pictureBox2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseDown);
			this->pictureBox2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseMove);
			this->pictureBox2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseUp);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(118, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(251, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Отрисовка с помощью алгоритмов Брезенхема";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(627, 31);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(232, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Отрисовка с помощью встроенных функций";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1010, 498);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Проект 1. Алгоритмы Брезенхема";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//Выбор отрисовки отрезков
		System::Void отрезкиToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		//Выбор отрисовки окружностей
		System::Void окружностиToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		//Выбор отрисовки эллипсов
		System::Void эллипсыToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		//Выбор очистки поля
		System::Void очиститьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		//Очистить выбор в меню
		void refreshMenuItems();

		//Срабатывает при зажимании мыши на левом picturebox
		System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		//Срабатывает при зажимании мыши на правом picturebox
		System::Void pictureBox2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		//Зажимание мыши на picturebox
		void mouseDown(int x, int y);

		//Срабатывает при передвижении мыши на левом picturebox
		System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		//Срабатывает при передвижении мыши на правом picturebox
		System::Void pictureBox2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		//Передвижение мыши на picturebox
		void mouseMove(int x, int y);

		//Срабатывает при отпускании мыши на левом picturebox
		System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		//Срабатывает при отпускании мыши на правом picturebox
		System::Void pictureBox2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		//Отпускание мыши на picturebox
		void mouseUp(int x, int y);

		//Пересировка левого picturebox
		System::Void pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

		//Пересировка правого picturebox
		System::Void pictureBox2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

		//Очищает данные
		void cleanData();

		//Сообщение о программе
		System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
