#include "Line.h"

namespace Brez {

	Line::Line(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	int Line::X1()
	{
		return this->x1;
	}

	int Line::Y1()
	{
		return this->y1;
	}

	int Line::X2()
	{
		return this->x2;
	}

	int Line::Y2()
	{
		return this->y2;
	}
}