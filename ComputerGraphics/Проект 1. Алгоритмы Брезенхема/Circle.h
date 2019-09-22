#pragma once

namespace Brez {
	//Класс окружностей
	ref class Circle
	{
	private:
		//Данные окружности
		int x, y, r;

	public:
		//Конструкор
		Circle(int x, int y, int r);

		//Возвращает x
		int X();

		//Возвращает y
		int Y();

		//Возвращает радиус
		int R();
	};
}

