#pragma once

namespace Brez {
	//����� ��������
	public ref class Line
	{
	protected:
		//���������� ������
		int x1, y1, x2, y2;

	public:
		//����������
		Line(int x1, int y1, int x2, int y2);

		//���������� x1
		int X1();

		//���������� y1
		int Y1();

		//���������� x2
		int X2();

		//���������� y2
		int Y2();
	};
}

