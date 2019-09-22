#pragma once

namespace Brez {
	//Класс отрезков
	public ref class Line
	{
	protected:
		//Координаты прямой
		int x1, y1, x2, y2;

	public:
		//Конструкор
		Line(int x1, int y1, int x2, int y2);

		//Возвращает x1
		int X1();

		//Возвращает y1
		int Y1();

		//Возвращает x2
		int X2();

		//Возвращает y2
		int Y2();
	};
}

