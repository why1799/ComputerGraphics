#pragma once

namespace KDZ2 {
	//Шаблон объекта
 class WorldObject {
	public:
		//Получить тип
		virtual int gettype() { return -1; };
		//Отрисовать
		virtual void draw() { };
		//Физика
		virtual void physics() { };
		//Продвижение
		virtual void advance(double dt) { };
	};
}