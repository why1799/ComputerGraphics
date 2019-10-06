#pragma once

namespace Brez {
	//Класс отрезков
	public ref class Line
	{
	public:
		//Координаты прямой
		int X1, Y1, X2, Y2;

	public:
		//Конструкор
		Line(int x1, int y1, int x2, int y2)
		{
			this->X1 = x1;
			this->Y1 = y1;
			this->X2 = x2;
			this->Y2 = y2;
		}
	};
}

