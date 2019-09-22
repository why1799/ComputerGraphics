#include "GraphicExtensions.h"
#include <math.h>

namespace Brez {

	using namespace System;

	void GraphicsExtensions::MyDrawLine(Graphics ^graphics, Brush ^brush, int x1, int y1, int x2, int y2)
	{
		int x = x1;
		int y = y1;
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int s1 = Math::Sign(x2 - x1);
		int s2 = Math::Sign(y2 - y1);
		bool c;

		if (dy > dx)
		{
			int tmp = dx;
			dx = dy;
			dy = tmp;
			c = true;
		}
		else
		{
			c = false;
		}

		int e = 2 * dy - dx;
		for (int i = 1; i <= dx; i++)
		{
			graphics->FillRectangle(brush, x, y, 1, 1);
			while (e >= 0)
			{
				if (c)
					x += s1;
				else
					y += s2;
				e -= 2 * dx;
			}
			if (c)
				y += s2;
			else
				x += s1;
			e += 2 * dy;
		}
	}
	void GraphicsExtensions::MyDrawRectangle(Graphics ^ graphics, Brush ^ brush, int x, int y, int width, int height)
	{
		if (width <= 0 || height <= 0)
			return;

		MyDrawLine(graphics, brush, x, y, x + width, y);
		MyDrawLine(graphics, brush, x, y, x, y + height);
		MyDrawLine(graphics, brush, x, y + height, x + width, y + height);
		MyDrawLine(graphics, brush, x + width, y, x + width, y + height);
	}
	void GraphicsExtensions::MyDrawCircle(Graphics ^ graphics, Brush ^ brush, int xc, int yc, int r)
	{
		int x = 0;
		int y = r;
		int d = 2 * (1 - r);
		int lim = 0;

		while(y >= lim){
			graphics->FillRectangle(brush, x + xc, y + yc, 1, 1);
			graphics->FillRectangle(brush, x + xc, yc - y, 1, 1);
			graphics->FillRectangle(brush, xc - x, y + yc, 1, 1);
			graphics->FillRectangle(brush, xc - x, yc - y, 1, 1);
			
			if (d < 0)
			{
				int b = 2 * d + 2 * y - 1;
				if (b <= 0)
				{
					x++;
					d += 2 * x + 1;
					continue;
				}
			}
			else if(d > 0)
			{
				int b = 2 * d - 2 * x - 1;
				if (b > 0)
				{
					y--;
					d += 1 - 2 * y;
					continue;
				}
			}

			x++;
			y--;
			d += 2 * x - 2 * y + 2;

		}
	}
	void GraphicsExtensions::MyDrawEllipse(Graphics ^ graphics, Brush ^ brush, int x1, int y1, int x2, int y2)
	{
		int xc = (x1 + x2) / 2;
		int yc = (y1 + y2) / 2;

		int d1 = Math::Abs(x2 - x1);
		int d2 = Math::Abs(y2 - y1);

		int x = 0;
		int y = d2 / 2;
		int a2 = d1 * d1 / 4;
		int b2 = d2 * d2 / 4;
		int d = 4 * b2 * ((x + 1) * (x + 1)) + a2 * ((2 * y - 1) * (2 * y - 1)) - 4 * a2 * b2;
		while (a2 * (2 * y - 1) > 2 * b2 * (x + 1))
		{
			graphics->FillRectangle(brush, x + xc, y + yc, 1, 1);
			graphics->FillRectangle(brush, x + xc, yc - y, 1, 1);
			graphics->FillRectangle(brush, xc - x, y + yc, 1, 1);
			graphics->FillRectangle(brush, xc - x, yc - y, 1, 1);
			if (d < 0)
			{
				x++;
				d += 4 * b2 * (2 * x + 3);
			}
			else
			{
				x++;
				y--;
				d -=  8 * a2 * y - 4 * b2 * (2 * x + 3);
			}
		}
		d = b2 * ((2 * x + 1) * (2 * x + 1)) + 4 * a2 * ((y + 1) * (y + 1)) - 4 * a2 * b2;
		while (y >= 0)
		{
			graphics->FillRectangle(brush, x + xc, y + yc, 1, 1);
			graphics->FillRectangle(brush, x + xc, yc - y, 1, 1);
			graphics->FillRectangle(brush, xc - x, y + yc, 1, 1);
			graphics->FillRectangle(brush, xc - x, yc - y, 1, 1);
			if (d < 0)
			{
				y--;
				d += 4 * a2 * (2 * y + 3);
			}
			else
			{
				y--;
				x++;
				d -= 8 * b2 * x - 4 * a2 * (2 * y + 3);
			}
		}
	}
}
