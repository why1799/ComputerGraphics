#pragma once

namespace Brez {
	//����� �����������
	ref class Circle
	{
	private:
		//������ ����������
		int x, y, r;

	public:
		//����������
		Circle(int x, int y, int r);

		//���������� x
		int X();

		//���������� y
		int Y();

		//���������� ������
		int R();
	};
}

