#pragma once
namespace Brez {

	using namespace System::Drawing;

	//����� ���������� ��� Graphics
	public class GraphicsExtensions final
	{
	public:
		//����� ��� ��������� ��������
		static void MyDrawLine(Graphics ^graphics, Brush ^brush, int x1, int y1, int x2, int y2);

		//����� ��� ��������� ��������������
		static void MyDrawRectangle(Graphics ^graphics, Brush ^brush, int x, int y, int width, int height);

		//����� ��� ��������� �����������
		static void MyDrawCircle(Graphics ^graphics, Brush ^brush, int x, int y, int r);

		//����� ��� ��������� �������
		static void MyDrawEllipse(Graphics ^graphics, Brush ^brush, int x1, int y1, int x2, int y2);
	};
}
