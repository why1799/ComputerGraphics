#pragma once
namespace Brez {

	using namespace System::Drawing;

	//Класс расширений для Graphics
	public class GraphicsExtensions final
	{
	public:
		//Метод для отрисовки отрезков
		static void MyDrawLine(Graphics ^graphics, Brush ^brush, int x1, int y1, int x2, int y2);

		//Метод для отрисовки прямоугольника
		static void MyDrawRectangle(Graphics ^graphics, Brush ^brush, int x, int y, int width, int height);

		//Метод для отрисовки окружностей
		static void MyDrawCircle(Graphics ^graphics, Brush ^brush, int x, int y, int r);

		//Метод для отрисовки эллипса
		static void MyDrawEllipse(Graphics ^graphics, Brush ^brush, int x1, int y1, int x2, int y2);
	};
}
