//�������� ���� ���������� ���161
//�������� ������� "������ 1. ��������� ����������"
//�������� � Visual Studio 2017, Windows 10
//��������� ��������� ��������, �����������, ��������, ������� ������ � ����� � ���������
//����� ���������� �������, ����������, ������ ��� ����� �������� �����,
//�������� ��������������� ����� �� ������� "�������������". ����� ������� ���� �� ����� �� ����� ���� � �������,
//����� ���������� ������. ����� ��������� ������ ����. 
//��� ������� �� ��������� ������:
//Circle.cpp
//Circle.h
//Ellipse.cpp
//Ellipse.h
//GraphicExtensions.cpp
//GraphicExtensions.h
//Line.cpp
//Line.h
//Main.cpp
//MyForm.cpp
//MyForm.h
//����� ����� ��������� � ����� Main.cpp

#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

//����� ����� ���������
[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Bez::MyForm form;
	Application::Run(%form);
}
