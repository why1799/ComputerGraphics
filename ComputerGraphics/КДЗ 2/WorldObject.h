#pragma once

namespace KDZ2 {
	//������ �������
 class WorldObject {
	public:
		//�������� ���
		virtual int gettype() { return -1; };
		//����������
		virtual void draw() { };
		//������
		virtual void physics() { };
		//�����������
		virtual void advance(double dt) { };
	};
}