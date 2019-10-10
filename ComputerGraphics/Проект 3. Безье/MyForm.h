#pragma once

#include <vector>
#include "MyPoint.h"

namespace Bez {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	private:
		List<MyPoint^>^ points;
		bool add;
		
		bool end;
		int rex = 5;
		int rin = 2;

		float draganddropaddx;
		float draganddropaddy;
		int draganddropitem;
		bool dad;
		float mousex;
	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::Button^ button4;
		   float mousey;

	public:
		MyForm(void)
		{
			InitializeComponent();
			points = gcnew List<MyPoint^>();



			radioButton1->Checked = true;
			panel3->Enabled = false;
			add = false;
			end = false;
			dad = false;
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
				delete points;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Panel^ panel3;

	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::RadioButton^ radioButton3;;



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox1->Location = System::Drawing::Point(297, 25);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(856, 809);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(4, 5);
			this->radioButton1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(182, 24);
			this->radioButton1->TabIndex = 1;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Безье 3-го порядка";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(4, 40);
			this->radioButton2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(182, 24);
			this->radioButton2->TabIndex = 2;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Безье n-го порядка";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->radioButton3);
			this->panel1->Controls->Add(this->radioButton1);
			this->panel1->Controls->Add(this->radioButton2);
			this->panel1->Location = System::Drawing::Point(18, 18);
			this->panel1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(233, 111);
			this->panel1->TabIndex = 3;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(4, 74);
			this->radioButton3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(104, 24);
			this->radioButton3->TabIndex = 3;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"B-сплайн";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton3_CheckedChanged);
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->checkBox5);
			this->panel2->Controls->Add(this->checkBox1);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->button1);
			this->panel2->Location = System::Drawing::Point(18, 152);
			this->panel2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(233, 192);
			this->panel2->TabIndex = 4;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(4, 128);
			this->checkBox5->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(219, 44);
			this->checkBox5->TabIndex = 8;
			this->checkBox5->Text = L"Прямая на опорных точ-\r\nках";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox5_CheckedChanged);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(4, 94);
			this->checkBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(131, 24);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Разный цвет";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(4, 49);
			this->button2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(186, 35);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Замкнуть ломаную";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(4, 5);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(186, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Добавить часть";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(18, 418);
			this->button3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(112, 35);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Очистить";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->checkBox3);
			this->panel3->Location = System::Drawing::Point(18, 354);
			this->panel3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(233, 54);
			this->panel3->TabIndex = 5;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(4, 5);
			this->checkBox3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(179, 24);
			this->checkBox3->TabIndex = 9;
			this->checkBox3->Text = L"Замкнуть ломаную";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox3_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(18, 463);
			this->checkBox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(266, 24);
			this->checkBox2->TabIndex = 8;
			this->checkBox2->Text = L"Отобразить опорную ломаную";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(18, 498);
			this->checkBox4->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(235, 64);
			this->checkBox4->TabIndex = 9;
			this->checkBox4->Text = L"Отобразить кривую Безье\r\nсозданную алгорит-\r\nмом Кастельжо";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox4_CheckedChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(13, 797);
			this->button4->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(141, 35);
			this->button4->TabIndex = 10;
			this->button4->Text = L"О программе";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1168, 846);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"MyForm";
			this->Text = L"Проект 3. Сплайновые кривые";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		

		
	}
	
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {


		Color^ c = gcnew Color();
		Pen^ pen = gcnew Pen(c->Red, 1);
		SolidBrush^ brush = gcnew SolidBrush(c->Red);
		
		pen->Color = c->LightGray;
		brush->Color = c->LightGray;

		if (checkBox5->Checked && points->Count >= 4)
		{
			for (int i = 0; i < points->Count; i++)
			{
				if (i % 3 == 0)
				{
					float x1, y1, x2, y2;
					if (i == 0 && end)
					{
						x1 = points[points->Count - 2]->X;
						y1 = points[points->Count - 2]->Y;

						x2 = points[1]->X;
						y2 = points[1]->Y;
					}
					else
					{
						if (!(i + 1 < points->Count) || i == 0)
							continue;

						x1 = points[i - 1]->X;
						y1 = points[i - 1]->Y;

						x2 = points[i + 1]->X;
						y2 = points[i + 1]->Y;
					}
					e->Graphics->DrawLine(pen, x1, y1, x2, y2);
				}
			}
		}

		pen->Color = c->Red;
		brush->Color = c->Red;

		if (checkBox1->Checked)
		{
			//Отрисовка опорных точек
			for (int i = 0; i < points->Count; i++)
			{
				if (i % 3 == 0)
				{
					pen->Color = c->Red;
					brush->Color = c->Red;
				}
				else
				{
					pen->Color = c->Green;
					brush->Color = c->Green;
				}

				if (i == draganddropitem && dad)
				{
					pen->Color = c->Blue;
					brush->Color = c->Blue;
				}
				e->Graphics->DrawEllipse(pen, points[i]->X - rex, points[i]->Y - rex, 2 * (float)rex, 2 * (float)rex);
				e->Graphics->FillEllipse(brush, points[i]->X - rin, points[i]->Y - rin, 2 * (float)rin, 2 * (float)rin);
			}
		}
		else
		{
			int i = 0;
			//Отрисовка опорных точек
			for each (auto p in points)
			{
				if (i == draganddropitem && dad)
				{
					pen->Color = c->Blue;
					brush->Color = c->Blue;
				}
					e->Graphics->DrawEllipse(pen, p->X - rex, p->Y - rex, 2 * (float)rex, 2 * (float)rex);
					e->Graphics->FillEllipse(brush, p->X - rin, p->Y - rin, 2 * (float)rin, 2 * (float)rin);
				if (i == draganddropitem && dad)
				{
					pen->Color = c->Red;
					brush->Color = c->Red;
				}
				i++;
			}
		}

		//Отрисовка опорной ломанной
		if (checkBox2->Checked)
		{
			for (int i = 1; i < points->Count; i++)
				e->Graphics->DrawLine(pen, points[i - 1]->X, points[i - 1]->Y, points[i]->X, points[i]->Y);
		}

		if (radioButton1->Checked)
		{
			if (points->Count >= 4)
			{
				List<MyPoint^>^ tmp = gcnew List<MyPoint^>();
				for (int i = 0; i < points->Count; i++)
				{
					tmp->Add(points[i]);
					if (tmp->Count % 4 == 0)
					{
						DrawBez3(e->Graphics, tmp);
						tmp = gcnew List<MyPoint^>();
						tmp->Add(points[i]);
					}
				}
			}
		}

		else if(radioButton2->Checked)
		{
			DrawBezN(e->Graphics);
		}
		else if (radioButton3->Checked)
		{
			if (points->Count >= 4)
			{
				List<MyPoint^>^ tmp = gcnew List<MyPoint^>();

				int l = checkBox3->Checked ? 1 : 0;
				for (int i = 0; i < points->Count - l; i++)
				{
					tmp->Add(points[i]);
					if (tmp->Count % 4 == 0)
					{
						DrawBSplain(e->Graphics, tmp);
						tmp = gcnew List<MyPoint^>();
						i -= 3;
					}
				}

				if (checkBox3->Checked)
				{
					tmp = gcnew List<MyPoint^>();
					tmp->Add(points[points->Count - 4]);
					tmp->Add(points[points->Count - 3]);
					tmp->Add(points[points->Count - 2]);
					tmp->Add(points[0]);
					DrawBSplain(e->Graphics, tmp);

					tmp = gcnew List<MyPoint^>();
					tmp->Add(points[points->Count - 3]);
					tmp->Add(points[points->Count - 2]);
					tmp->Add(points[0]);
					tmp->Add(points[1]);
					DrawBSplain(e->Graphics, tmp);

					tmp = gcnew List<MyPoint^>();
					tmp->Add(points[points->Count - 2]);
					tmp->Add(points[0]);
					tmp->Add(points[1]);
					tmp->Add(points[2]);
					DrawBSplain(e->Graphics, tmp);
				}
			}
		}

		if (points->Count >= 2 && checkBox4->Checked)
		{
			DrawCasteljau(e->Graphics);
		}

		delete c;
		delete pen;
		delete brush;
	}


		   void DrawBSplain(Graphics^ g, List<MyPoint^>^ points)
		   {
			   Color^ c = gcnew Color();
			   Pen^ pen = gcnew Pen(c->Black);

			   float xprev;
			   float yprev;

			   for (int s = 0; s <= 100; s += 1)
			   {
				   float t = s / 100.0;
				   float x = 1 / 6.0 * (Math::Pow(1 - t, 3) * points[0]->X + (3 * t * t * t - 6 * t * t + 4) * points[1]->X + (-3 * t * t * t + 3 * t * t + 3 * t + 1) * points[2]->X + t * t * t * points[3]->X);
				   float y = 1 / 6.0 * (Math::Pow(1 - t, 3) * points[0]->Y + (3 * t * t * t - 6 * t * t + 4) * points[1]->Y + (-3 * t * t * t + 3 * t * t + 3 * t + 1) * points[2]->Y + t * t * t * points[3]->Y);
				   if (t != 0)
				   {
					   g->DrawLine(pen, xprev, yprev, x, y);
				   }
				   xprev = x;
				   yprev = y;
			   }

			   delete c;
			   delete pen;
		   }

		   void DrawCasteljau(Graphics^ g)
		   {
			   Color^ c = gcnew Color();
			   Pen^ pen = gcnew Pen(c->Green);

			   float xprev, yprev;

			   for (int s = 0; s <= 100; s++)
			   {
				   float t = s / 100.0;

				   auto point = DrawCasteljau(g, points, t);

				   if (s != 0)
				   {
					   g->DrawLine(pen, xprev, yprev, point->X, point->Y);
				   }

				   xprev = point->X;
				   yprev = point->Y;

				   delete point;
			   }

			   delete c;
			   delete pen;
		   }

		   MyPoint^ DrawCasteljau(Graphics^ g, List<MyPoint^>^ pl, float t)
		   {
			   if (pl->Count == 2)
			   {
				   float xx1 = (pl[1]->X - pl[0]->X) * t + pl[0]->X;
				   float yy1 = (pl[1]->Y - pl[0]->Y) * t + pl[0]->Y;
				   return gcnew MyPoint(xx1, yy1);
			   }
			   else if (pl->Count == 3)
			   {
				   float xx1 = (pl[1]->X - pl[0]->X) * t + pl[0]->X;
				   float yy1 = (pl[1]->Y - pl[0]->Y) * t + pl[0]->Y;

				   float xx2 = (pl[2]->X - pl[1]->X) * t + pl[1]->X;
				   float yy2 = (pl[2]->Y - pl[1]->Y) * t + pl[1]->Y;

				   float xx3 = (xx2 - xx1) * t + xx1;
				   float yy3 = (yy2 - yy1) * t + yy1;

				   return gcnew MyPoint(xx3, yy3);
			   }
			   else
			   {
				   List<MyPoint^>^ psnew = gcnew List<MyPoint^>();
				   for (int i = 1; i < pl->Count; i++)
				   {
					   float xx1 = (pl[i]->X - pl[i - 1]->X) * t + pl[i - 1]->X;
					   float yy1 = (pl[i]->Y - pl[i - 1]->Y) * t + pl[i - 1]->Y;

					   psnew->Add(gcnew MyPoint(xx1, yy1));
				   }
				   return DrawCasteljau(g, psnew, t);
			   }
		   }

		   //Рисует кривую безье третьей степени
		   void DrawBez3(Graphics^ g, List<MyPoint^>^ points)
		   {
			   Color^ c = gcnew Color();
			   Pen^ pen = gcnew Pen(c->Black);

			   float xprev;
			   float yprev;

			   for (int s = 0; s <= 100; s += 1)
			   {
				   float t = s / 100.0;
				   float x = Math::Pow((1 - t), 3) * points[0]->X + 3 * t * Math::Pow((1 - t), 2) * points[1]->X + 3 * t * t * (1 - t) * points[2]->X + t * t * t * points[3]->X;
				   float y = Math::Pow((1 - t), 3) * points[0]->Y + 3 * t * Math::Pow((1 - t), 2) * points[1]->Y + 3 * t * t * (1 - t) * points[2]->Y + t * t * t * points[3]->Y;
				   if (t != 0)
				   {
					   g->DrawLine(pen, xprev, yprev, x, y);
				   }
				   xprev = x;
				   yprev = y;
			   }

			   delete c;
			   delete pen;
		   }

		   //Рисует кривую безье n-ой степени
		   void DrawBezN(Graphics^ g)
		   {
			   Color^ c = gcnew Color();
			   Pen^ pen = gcnew Pen(c->Black);

			   float xprev;
			   float yprev;

			   for (int s = 0; s <= 100; s += 1)
			   {
				   float t = s / 100.0;
				   float x = 0;
				   float y = 0;

				   for (int i = 0; i < points->Count; i++)
				   {
					   float n = points->Count - 1;
					   //float p = fac(n) / float(fac(i)*fac(n - i)) * Math::Pow(t, i) * Math::Pow((1 - t), n - i);
					   float p = C(n, i) * Math::Pow(t, i) * Math::Pow((1 - t), n - i);
					   x += p * points[i]->X;
					   y += p * points[i]->Y;
				   }
				   if (t != 0)
				   {
					   g->DrawLine(pen, xprev, yprev, x, y);
				   }
				   xprev = x;
				   yprev = y;
			   }

			   delete c;
			   delete pen;
		   }

		   //Считает факториал
		   long long fac(int n)
		   {
			   long long i = 1;
			   for (int j = 1; j <= n; j++)
			   {
				   i *= j;
			   }
			   return i;
		   }

		   long long C(int n, int k)
		   {
			   if ((n == k) || (k == 0)) {
				   return 1;
			   }
			   if (k == 1) {
				   return n;
			   }
			   return C(n - 1, k) + C(n - 1, k - 1);
		   }
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->Refresh();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		points = gcnew List<MyPoint^>();
		checkBox3->Checked = false;
		end = false;
		pictureBox1->Refresh();
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButton1->Checked)
		{
			points = gcnew List<MyPoint^>;
			pictureBox1->Refresh();
			panel3->Enabled = false;
			panel2->Enabled = true;
			checkBox3->Checked = false;
			end = false;
		}
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButton2->Checked)
		{
			pictureBox1->Refresh();
			panel3->Enabled = true;
			panel2->Enabled = false;
			checkBox1->Checked = false;
			checkBox5->Checked = false;
			end = false;
		}
	}
	private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButton3->Checked)
		{
			pictureBox1->Refresh();
			panel3->Enabled = true;
			panel2->Enabled = false;
			checkBox1->Checked = false;
			checkBox5->Checked = false;
			end = false;
		}
	}
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {


		if (points->Count > 0)
		{
			if (checkBox3->Checked)
			{
				points->Add(gcnew MyPoint(points[0]->X, points[0]->Y));
			}
			else
			{
				points->RemoveAt(points->Count - 1);
			}
		}
		else
		{
			checkBox3->Checked = false;
		}
		pictureBox1->Refresh();
	}
	private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->Refresh();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (points->Count >= 4 && (points->Count == 4 || (points->Count - 4) % 3 == 0) && radioButton1->Checked && !end)
		{
			auto f = points[points->Count - 1];
			auto s = points[points->Count - 2];

			points->Add(gcnew MyPoint(2 * f->X - s->X, 2 * f->Y - s->Y));
			pictureBox1->Refresh();
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (points->Count >= 4 && (points->Count - 4) % 3 == 1 && radioButton1->Checked && !end)
		{
			auto f = points[0];
			auto s = points[1];

			points->Add(gcnew MyPoint(2 * f->X - s->X, 2 * f->Y - s->Y));
			points->Add(points[0]);
			end = true;
			pictureBox1->Refresh();
		}
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->Refresh();
	}

	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (add)
		{
			if (radioButton1->Checked)
			{
				if (points->Count >= 4 && (points->Count == 4 || (points->Count - 4) % 3 == 0))
				{
					return;
				}
			}

			if (checkBox3->Checked && points->Count > 1)
			{
				points->Insert(points->Count - 1, gcnew MyPoint(e->Location.X, e->Location.Y));
			}
			else
			{
				points->Add(gcnew MyPoint(e->Location.X, e->Location.Y));
			}
		}
		else if(dad)
		{
			dad = false;
		}

		pictureBox1->Refresh();
	}
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		add = false;
		if (dad)
		{
			mousex = e->Location.X;
			mousey = e->Location.Y;

			if (radioButton1->Checked)
			{
				float oldx = points[draganddropitem]->X;
				float oldy = points[draganddropitem]->Y;
				if (draganddropitem % 3 == 0)
				{
					points[draganddropitem]->X = mousex + draganddropaddx;
					points[draganddropitem]->Y = mousey + draganddropaddy;
					float changex = points[draganddropitem]->X - oldx;
					float changey = points[draganddropitem]->Y - oldy;
					if ((draganddropitem == 0 || draganddropitem == points->Count - 1) && end)
					{
						points[1]->X += changex;
						points[1]->Y += changey;

						points[points->Count - 2]->X += changex;
						points[points->Count - 2]->Y += changey;
					}
					else
					{
						if (draganddropitem + 1 < points->Count && draganddropitem != 0)
						{
							points[draganddropitem - 1]->X += changex;
							points[draganddropitem - 1]->Y += changey;

							points[draganddropitem + 1]->X += changex;
							points[draganddropitem + 1]->Y += changey;
						}
					}
				}
				if (draganddropitem % 3 == 1)
				{
					points[draganddropitem]->X = mousex + draganddropaddx;
					points[draganddropitem]->Y = mousey + draganddropaddy;
					float changex = points[draganddropitem]->X - oldx;
					float changey = points[draganddropitem]->Y - oldy;
					if (draganddropitem == 1 && end)
					{
						points[points->Count - 2]->X -= changex;
						points[points->Count - 2]->Y -= changey;
					}
					else
					{
						if (draganddropitem != 1)
						{
							points[draganddropitem - 2]->X -= changex;
							points[draganddropitem - 2]->Y -= changey;
						}
					}
				}
				if (draganddropitem % 3 == 2)
				{
					points[draganddropitem]->X = mousex + draganddropaddx;
					points[draganddropitem]->Y = mousey + draganddropaddy;
					float changex = points[draganddropitem]->X - oldx;
					float changey = points[draganddropitem]->Y - oldy;
					if (draganddropitem == points->Count - 2 && end)
					{
						points[1]->X -= changex;
						points[1]->Y -= changey;
					}
					else
					{
						if (draganddropitem + 2 < points->Count && draganddropitem != points->Count - 2)
						{
							points[draganddropitem + 2]->X -= changex;
							points[draganddropitem + 2]->Y -= changey;
						}
					}
				}

			}
			else
			{
				points[draganddropitem]->X = mousex + draganddropaddx;
				points[draganddropitem]->Y = mousey + draganddropaddy;
			}
			

			if (checkBox3->Checked && (draganddropitem == 0 || draganddropitem == points->Count - 1))
			{
				points[points->Count - 1]->X = points[0]->X = mousex + draganddropaddx;
				points[points->Count - 1]->Y = points[0]->Y = mousey + draganddropaddy;
			}
		}

		

		

		pictureBox1->Refresh();
	}
	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		add = true;

		int i = 0;
		for each(auto point in points)
		{
			if (Math::Sqrt((point->X - e->Location.X) * (point->X - e->Location.X) + (point->Y - e->Location.Y) * (point->Y - e->Location.Y)) <= rex)
			{
				add = false;
				dad = true;
				draganddropaddx = point->X - e->Location.X;
				draganddropaddy = point->Y - e->Location.Y;
				draganddropitem = i;
				pictureBox1->Refresh();
				return;
			}
			i++;
		}
	}
private: System::Void checkBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	pictureBox1->Refresh();
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Харченко Артём Витальевич БПИ161\n\nДомашнее задание \"Проект 3. Сплайновые кривые\"\nНаписано в Visual Studio 2019, Windows 10\n\nВыполнено отрисовка Безье 3-его порядка, возможность делать составную ломаную, замкнуть её. Отрисовка прямых на опорных точках, разный цвет опорных точек\nВыполнена отрисовка Безье n-ого порядка, возможность её замыкать\nВыполнена отрисовка кривых B-сплайн, возможность её замыкать\nМожно отоброжать опорную ломаную\nМожно отобразить кривую Безье созданную алгоритмом Кастельжо по опорным точкам\nМожно очистить экран\nМожно переносить точки\nЕсть пункт о программе");
}
};
}
