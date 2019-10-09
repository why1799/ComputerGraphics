//Харченко Артём Витальевич БПИ161
//Домашнее задание "Проект 1. Алгоритмы Брезенхема"
//Написано в Visual Studio 2017, Windows 10
//Выполнена отрисовка отрезков, окружностей, эллипсов, очистка экрана и пункт о программе
//Чтобы нарисовать отрезок, окружность, эллипс или чтобы очистить экран,
//выберите соответствующий пункт во вкладке "Редактировать". Затем зажмите мышь на одной из белом поле и проведи,
//чтобы нарисовать объект. После отпустите кнопку мыши. 
//Код разделён на нескольно файлов:
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
//Точка входа находится в файле Main.cpp

#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

//Точка входа программы
[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Bez::MyForm form;
	Application::Run(%form);
}
