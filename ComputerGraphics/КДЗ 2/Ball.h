#pragma once

#include "WorldObject.h"
#include <gl\glut.h>

#define BALL  1

namespace KDZ2 {
	//Объект типа мяч
	class Ball : public WorldObject {
	public:
		double px, py, pz;
		double vx, vy, vz;
		double ax, ay, az;
		double r, m, elasticity, friction;
		GLUquadricObj* glsphere;

		//Коструктор
		Ball(double x, double y, double z, double radius, double mass, double elast, double frict) {
			px = x;
			py = y;
			pz = z;
			r = radius;
			m = mass;
			elasticity = elast;
			friction = frict;
			vx = vy = vz = ax = ay = az = 0.0;
			glsphere = gluNewQuadric();
		};

		int gettype() { return BALL; };
		void physics();
		void advance(double dt);
		void draw();
	};
}