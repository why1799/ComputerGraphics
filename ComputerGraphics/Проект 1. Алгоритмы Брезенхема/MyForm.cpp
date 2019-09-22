#include "MyForm.h"

namespace Brez {

	MyForm::MyForm(void)
	{
		InitializeComponent();
		state = State::LineDraw;
		�������ToolStripMenuItem->Checked = true;
		this->lines = (gcnew List<Line^>());
		this->circles = (gcnew List<Circle^>());
		this->ellipses = (gcnew List<Ellipse^>());
		mousedown = false;
	}
	MyForm::~MyForm()
	{
		if (components)
		{
			delete components;
		}
		cleanData();
	}
	System::Void MyForm::�������ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		state = State::LineDraw;
		refreshMenuItems();
		�������ToolStripMenuItem->Checked = true;
	}
	System::Void MyForm::����������ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		state = State::�ircleDraw;
		refreshMenuItems();
		����������ToolStripMenuItem->Checked = true;
	}
	System::Void MyForm::�������ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		state = State::EllipseDraw;
		refreshMenuItems();
		�������ToolStripMenuItem->Checked = true;
	}
	System::Void MyForm::��������ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		cleanData();
		lines = (gcnew List<Line^>());
		circles = (gcnew List<Circle^>());
		ellipses = (gcnew List<Ellipse^>());
		pictureBox1->Refresh();
		pictureBox2->Refresh();
	}
	void MyForm::refreshMenuItems()
	{
		�������ToolStripMenuItem->Checked = false;
		����������ToolStripMenuItem->Checked = false;
		�������ToolStripMenuItem->Checked = false;
	}
	System::Void MyForm::pictureBox1_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		mouseDown(e->Location.X, e->Location.Y);
	}
	System::Void MyForm::pictureBox2_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		mouseDown(e->Location.X, e->Location.Y);
	}
	void MyForm::mouseDown(int x, int y)
	{
		mousedown = true;
		this->x1 = x;
		this->y1 = y;
		this->x2 = x;
		this->y2 = y;
	}
	System::Void MyForm::pictureBox1_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		mouseMove(e->Location.X, e->Location.Y);
	}
	System::Void MyForm::pictureBox2_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		mouseMove(e->Location.X, e->Location.Y);
	}
	void MyForm::mouseMove(int x, int y)
	{
		if (mousedown)
		{
			Color ^col = gcnew Color();
			SolidBrush ^brush = gcnew SolidBrush(col->Red);
			Pen ^pen = gcnew Pen(col->Red);

			this->x2 = x;
			this->y2 = y;

			int r;
			switch (state)
			{
			case LineDraw:
				pictureBox1->Refresh();
				GraphicsExtensions::MyDrawLine(pictureBox1->CreateGraphics(), brush, this->x1, this->y1, this->x2, this->y2);
				pictureBox2->Refresh();
				pictureBox2->CreateGraphics()->DrawLine(pen, this->x1, this->y1, this->x2, this->y2);
				break;
			case �ircleDraw:
				r = (int)Math::Sqrt((this->x1 - this->x2) * (this->x1 - this->x2) + (this->y1 - this->y2) * (this->y1 - this->y2));
				pictureBox1->Refresh();
				GraphicsExtensions::MyDrawLine(pictureBox1->CreateGraphics(), brush, this->x1, this->y1, this->x2, this->y2);
				GraphicsExtensions::MyDrawCircle(pictureBox1->CreateGraphics(), brush, this->x1, this->y1, r);

				pictureBox2->Refresh();
				pictureBox2->CreateGraphics()->DrawLine(pen, this->x1, this->y1, this->x2, this->y2);
				pictureBox2->CreateGraphics()->DrawEllipse(pen, this->x1 - r, this->y1 - r, r * 2, r * 2);
				break;
			case EllipseDraw:
				pictureBox1->Refresh();
				GraphicsExtensions::MyDrawRectangle(pictureBox1->CreateGraphics(), brush, Math::Min(this->x1, this->x2), Math::Min(this->y1, this->y2), Math::Abs(this->x2 - this->x1), Math::Abs(this->y2 - this->y1));
				GraphicsExtensions::MyDrawEllipse(pictureBox1->CreateGraphics(), brush, this->x1, this->y1, this->x2, this->y2);

				pictureBox2->Refresh();
				pictureBox2->CreateGraphics()->DrawRectangle(pen, Math::Min(this->x1, this->x2), Math::Min(this->y1, this->y2), Math::Abs(this->x2 - this->x1), Math::Abs(this->y2 - this->y1));
				pictureBox2->CreateGraphics()->DrawEllipse(pen, this->x1, this->y1, this->x2 - this->x1, this->y2 - this->y1);
				break;
			default:
				break;
			}

			delete col;
			delete brush;
			delete pen;
		}
	}
	System::Void MyForm::pictureBox1_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		mouseUp(e->Location.X, e->Location.Y);
	}
	System::Void MyForm::pictureBox2_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		mouseUp(e->Location.X, e->Location.Y);
	}
	void MyForm::mouseUp(int x, int y)
	{
		this->x2 = x;
		this->y2 = y;
		mousedown = false;
		
		int r;
		switch (state)
		{
		case LineDraw:
			lines->Add(gcnew Line(this->x1, this->y1, this->x2, this->y2));
			break;
		case �ircleDraw:
			r = (int)Math::Sqrt((this->x1 - this->x2) * (this->x1 - this->x2) + (this->y1 - this->y2) * (this->y1 - this->y2));
			circles->Add(gcnew Circle(this->x1, this->y1, r));
			break;
		case EllipseDraw:
			ellipses->Add(gcnew Ellipse(this->x1, this->y1, this->x2, this->y2));
			break;
		default:
			break;
		}

		pictureBox1->Refresh();
		pictureBox2->Refresh();
	}
	System::Void MyForm::pictureBox1_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
	{
		Color ^col = gcnew Color();
		SolidBrush ^brush = gcnew SolidBrush(col->Black);
		for each (auto line in lines)
		{
			GraphicsExtensions::MyDrawLine(e->Graphics, brush, line->X1(), line->Y1(), line->X2(), line->Y2());
		}

		delete brush;
		brush = gcnew SolidBrush(col->Green);

		for each (auto circle in circles)
		{
			GraphicsExtensions::MyDrawCircle(e->Graphics, brush, circle->X(), circle->Y(), circle->R());
		}

		delete brush;
		brush = gcnew SolidBrush(col->Blue);

		for each (auto ellipse in ellipses)
		{
			GraphicsExtensions::MyDrawEllipse(e->Graphics, brush, ellipse->X1(), ellipse->Y1(), ellipse->X2(), ellipse->Y2());
		}


		delete col;
		delete brush;
	}
	System::Void MyForm::pictureBox2_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
	{
		Color ^col = gcnew Color();
		Pen ^pen = gcnew Pen(col->Black);
		for each (auto line in lines)
		{
			e->Graphics->DrawLine(pen, line->X1(), line->Y1(), line->X2(), line->Y2());
		}

		delete pen;
		pen = gcnew Pen(col->Green);

		for each (auto circle in circles)
		{
			e->Graphics->DrawEllipse(pen, circle->X() - circle->R(), circle->Y() - circle->R(), circle->R() * 2, circle->R() * 2);
		}

		delete pen;
		pen = gcnew Pen(col->Blue);

		for each (auto ellipse in ellipses)
		{
			e->Graphics->DrawEllipse(pen, ellipse->X1(), ellipse->Y1(), ellipse->X2() - ellipse->X1(), ellipse->Y2() - ellipse->Y1());
		}

		delete col;
		delete pen;
	}
	void MyForm::cleanData()
	{
		for each (auto line in lines)
		{
			delete line;
		}
		for each (auto circle in circles)
		{
			delete circle;
		}
		for each (auto ellipse in ellipses)
		{
			delete ellipse;
		}

		delete lines;
		delete circles;
		delete ellipses;
	}
	System::Void MyForm::����������ToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		MessageBox::Show("�������� ���� ���������� ���161\n�������� ������� \"������ 1. ��������� ����������\"\n�������� � Visual Studio 2017, Windows 10\n\n��������� ��������� ��������, �����������, ��������, ������� ������ � ����� � ���������.\n\n����� ���������� �������, ����������, ������ ��� ����� �������� �����, �������� ��������������� ����� �� ������� \"�������������\". ����� ������� ���� �� ����� �� ����� ���� � �������, ����� ���������� ������. ����� ��������� ������ ����.\n\n��� ������� �� ��������� ������:\nCircle.cpp\nCircle.h\nEllipse.cpp\nEllipse.h\nGraphicExtensions.cpp\nGraphicExtensions.h\nLine.cpp\nLine.h\nMain.cpp\nMyForm.cpp\nMyForm.h\n����� ����� ��������� � ����� Main.cpp");
	}
}
