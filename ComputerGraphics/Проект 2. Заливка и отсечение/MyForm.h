#pragma once

#include "Line.h"

namespace Brez {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public enum State {
		LineDraw, FormDraw
	};

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	public:
		List<Line^>^ lines;
		State state;
		int x, y, x2, y2;
		bool draw;

	public:
		MyForm(void)
		{
			InitializeComponent();
			this->lines = (gcnew List<Line^>());
			state = State::LineDraw;
			�������ToolStripMenuItem->Checked = true;
			draw = false;
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �����������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���������ToolStripMenuItem;

	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox1->Location = System::Drawing::Point(12, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(791, 540);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->����ToolStripMenuItem,
					this->����������ToolStripMenuItem, this->�����������ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(815, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->��������ToolStripMenuItem,
					this->�������������ToolStripMenuItem, this->���������ToolStripMenuItem
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// ��������ToolStripMenuItem
			// 
			this->��������ToolStripMenuItem->Name = L"��������ToolStripMenuItem";
			this->��������ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->��������ToolStripMenuItem->Text = L"��������";
			// 
			// �������������ToolStripMenuItem
			// 
			this->�������������ToolStripMenuItem->Name = L"�������������ToolStripMenuItem";
			this->�������������ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->�������������ToolStripMenuItem->Text = L"�������������";
			// 
			// ���������ToolStripMenuItem
			// 
			this->���������ToolStripMenuItem->Name = L"���������ToolStripMenuItem";
			this->���������ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->���������ToolStripMenuItem->Text = L"���������";
			// 
			// ����������ToolStripMenuItem
			// 
			this->����������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�������ToolStripMenuItem,
					this->�����ToolStripMenuItem
			});
			this->����������ToolStripMenuItem->Name = L"����������ToolStripMenuItem";
			this->����������ToolStripMenuItem->Size = System::Drawing::Size(86, 20);
			this->����������ToolStripMenuItem->Text = L"����������";
			// 
			// �������ToolStripMenuItem
			// 
			this->�������ToolStripMenuItem->Name = L"�������ToolStripMenuItem";
			this->�������ToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->�������ToolStripMenuItem->Text = L"�������";
			this->�������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�������ToolStripMenuItem_Click);
			// 
			// �����ToolStripMenuItem
			// 
			this->�����ToolStripMenuItem->Name = L"�����ToolStripMenuItem";
			this->�����ToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->�����ToolStripMenuItem->Text = L"�����";
			this->�����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�����ToolStripMenuItem_Click);
			// 
			// �����������ToolStripMenuItem
			// 
			this->�����������ToolStripMenuItem->Name = L"�����������ToolStripMenuItem";
			this->�����������ToolStripMenuItem->Size = System::Drawing::Size(103, 20);
			this->�����������ToolStripMenuItem->Text = L"� ����������";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(815, 579);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"���������";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		draw = true;
		x = e->Location.X;
		y = e->Location.Y;
	}
	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (draw)
		{
			x2 = e->Location.X;
			y2 = e->Location.Y;
			pictureBox1->Refresh();
			Color^ color = gcnew Color();
			Pen^ pen1 = gcnew Pen(color->Red, 2);
			Pen^ pen2 = gcnew Pen(color->Black, 2);
			switch (state)
			{
			case Brez::LineDraw:
				pictureBox1->CreateGraphics()->DrawLine(pen1, x, y, x2, y2);
				break;
			case Brez::FormDraw:
				pictureBox1->CreateGraphics()->DrawRectangle(pen2, Math::Min(x, x2), Math::Min(y, y2), Math::Abs(x2 - x), Math::Abs(y2 - y));
				break;
			default:
				break;
			}
			delete color;
			delete pen1;
			delete pen2;
		}

	}
	private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (draw)
		{
			draw = false;
			switch (state)
			{
			case Brez::LineDraw:
				lines->Add(gcnew Line(x, y, e->Location.X, e->Location.Y));
				break;
			case Brez::FormDraw:
				DoCut();
				break;
			default:
				break;
			}
			pictureBox1->Refresh();
		}
	}
	private: System::Void �������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		�������ToolStripMenuItem->Checked = true;
		�����ToolStripMenuItem->Checked = false;
		state = State::LineDraw;
	}
private: System::Void �����ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	�������ToolStripMenuItem->Checked = false;
	�����ToolStripMenuItem->Checked = true;
	state = State::FormDraw;
}
private: System::Void pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	Color^ color = gcnew Color();
	Pen^ pen = gcnew Pen(color->Black);
	for each (auto line in lines)
	{
		if (state == State::FormDraw && draw)
		{
			int c1 = outCode(line->X1, line->Y1, x, y, x2, y2);
			int c2 = outCode(line->X2, line->Y2, x, y, x2, y2);
			if ((c1 & c2) == 0)
			{
				if (c1 != 0 || c2 != 0)
				{
					if (x - x2 == 0 || y - y2 == 0)
					{
						pen->Color = color->Yellow;
					}
					else
					{


						pen->Color = color->Yellow;
					}
				}
				else
					pen->Color = color->Green;
			}
			else
				pen->Color = color->Red;
		}
		pen->Width = 2;
		e->Graphics->DrawLine(pen, line->X1, line->Y1, line->X2, line->Y2);
	}
	delete color;
	delete pen;
}


		 int outCode(int x, int y, int X1, int Y1, int X2, int Y2)
		 {
			 int x0 = Math::Min(X1, X2);
			 int y0 = Math::Min(Y1, Y2);
			 int x1 = Math::Max(X1, X2);
			 int y1 = Math::Max(Y1, Y2);

			 int code = 0;
			 if (x > x0) code |= 0x01;
			 if (x < x1) code |= 0x02;
			 if (y > y0) code |= 0x04;
			 if (y < y1) code |= 0x08;
			 return code;
		 }
private: System::Void MyForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
}

		 float M(int x1, int y1, int x2, int y2)
		 {
			 return (y2 - y1) / (float)(x2 - x1);
		 }

		 void DoCut()
		 {
			 for (int i = 0; i < lines->Count; i++)
			 {
				 int c1 = outCode(lines[i]->X1, lines[i]->Y1, x, y, x2, y2);
				 int c2 = outCode(lines[i]->X2, lines[i]->Y2, x, y, x2, y2);
				 if ((c1 & c2) == 0)
				 {
					 if (x - x2 == 0)
					 {
						 if (lines[i]->Y1 < lines[i]->Y2)
						 {
							 if (lines[i]->Y1 < Math::Min(y, y2))
							 {
								 lines[i]->Y1 = Math::Min(y, y2);
							 }

							 if (lines[i]->Y2 < Math::Max(y, y2))
							 {
								 lines[i]->Y2 = Math::Max(y, y2);
							 }
						 }

						 else 
						 {
							 if (lines[i]->Y2 < Math::Min(y, y2))
							 {
								 lines[i]->Y2 = Math::Min(y, y2);
							 }

							 if (lines[i]->Y1 < Math::Max(y, y2))
							 {
								 lines[i]->Y1 = Math::Max(y, y2);
							 }
						 }

						 continue;
					 }

					 if (y - y2 == 0)
					 {
						 if (lines[i]->X1 < lines[i]->X2)
						 {
							 if (lines[i]->X1 < Math::Min(x, x2))
							 {
								 lines[i]->X1 = Math::Min(x, x2);
							 }

							 if (lines[i]->X2 < Math::Max(x, x2))
							 {
								 lines[i]->X2 = Math::Max(x, x2);
							 }
						 }

						 else
						 {
							 if (lines[i]->Y2 < Math::Min(y, y2))
							 {
								 lines[i]->Y2 = Math::Min(y, y2);
							 }

							 if (lines[i]->Y1 < Math::Max(y, y2))
							 {
								 lines[i]->Y1 = Math::Max(y, y2);
							 }
						 }

						 continue;
					 }

					 if (c1 != 0 || c2 != 0)
					 {

					 }
				 }
				 else
				 {
					 lines->RemoveAt(i);
					 i--;
				 }
			 }
		 }
};

	
}
