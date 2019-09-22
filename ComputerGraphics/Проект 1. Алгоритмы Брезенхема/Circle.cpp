#include "Circle.h"

namespace Brez {
	Circle::Circle(int x, int y, int r)
	{
		this->x = x;
		this->y = y;
		this->r = r;
	}
	int Circle::X()
	{
		return x;
	}
	int Circle::Y()
	{
		return y;
	}
	int Circle::R()
	{
		return r;
	}
}
