#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <clocale>
#include <GL/freeglut.h>

#include "WorldObject.h"

#define NOCOLLISION   0
#define FASTCOLLISION 1

#define NOSUBDIVISION 0
#define SUBDIVISION1  1

#define CLOTH 0
#define BALL  1

#define SUBTREE  0
#define SUBDATA  1

//Начальные данные
#define OBJECTS 2
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

namespace KDZ2
{

	//Вектор
	typedef struct {
		double x, y, z;
	} VECTOR3D;

	//Точка
	typedef struct {
		double x, y, z;
		int fixed;
	} POINT3D;

	typedef struct {
		int id1, id2;
		double l;
	} SPRING;

	typedef struct QUADTREE {
		int tag;
		double xa, ya, za, xb, yb, zb;
		int x1, y1, x2, y2;
		QUADTREE* l1, * l2, * l3, * l4;
	} QUADTREE;
	

	double aspect_ratio = 0; //Соотношение сторон
	double camspeed = 0.2; //Скорость камеры
	double time_step = 0.002; //Временной шаг
	double camx = 0.0, camy = 0.5, camz = 2.0, viewx = 0.0, viewy = 0.0, viewz = -1.0; //Положение камеры
	double gravity = 9.81; //Гравитация
	bool light_switch = true; //Освещение
	WorldObject* obj[OBJECTS]; //Массив объектов

	//Нормализованный вектор по трём точкам
	void normalv(POINT3D pt1, POINT3D pt2, POINT3D pt3, VECTOR3D& ptn) {
		double x1 = pt2.x - pt1.x;
		double y1 = pt2.y - pt1.y;
		double z1 = pt2.z - pt1.z;
		double x2 = pt3.x - pt1.x;
		double y2 = pt3.y - pt1.y;
		double z2 = pt3.z - pt1.z;
		ptn.x = y1 * z2 - y2 * z1;
		ptn.y = z1 * x2 - z2 * x1;
		ptn.z = x1 * y2 - x2 * y1;
	}

	//Минимальный по 4ём
	double min4(double x1, double x2, double x3, double x4) {
		if (x2 < x1) x1 = x2;
		if (x3 < x1) x1 = x3;
		if (x4 < x1) x1 = x4;
		return x1;
	}

	//Максимальный по 4ём
	double max4(double x1, double x2, double x3, double x4) {
		if (x2 > x1) x1 = x2;
		if (x3 > x1) x1 = x3;
		if (x4 > x1) x1 = x4;
		return x1;
	}

	class ball : public WorldObject {
	public:
		double px, py, pz;
		double vx, vy, vz;
		double ax, ay, az;
		double r, m, elasticity, friction;
		GLUquadricObj* glsphere;

		ball(double x, double y, double z, double radius, double mass, double elast, double frict) {
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

	void ball::physics() {
		ax = 0.0;
		ay = -gravity;
		az = 0.0;

		if (py < r) {
			py = r;
			vx *= friction;
			vy *= -elasticity;
			vz *= friction;
		}

		int i;
		for (i = 0; obj[i] != this; i++);
		for (i++; i < OBJECTS; i++) {
			if (obj[i]->gettype() == BALL) {
				ball* b = (ball*)obj[i];
				double dx = px - b->px;
				double dy = py - b->py;
				double dz = pz - b->pz;
				double d = sqrt(dx * dx + dy * dy + dz * dz);
				if (d < r + b->r) {
					dx /= d; dy /= d; dz /= d;
					double v1i = dx * vx + dy * vy + dz * vz;
					double v2i = dx * b->vx + dy * b->vy + dz * b->vz;
					double v1f = (v1i * (m - b->m) + 2 * b->m * v2i) / (m + b->m) * friction;
					double v2f = (v2i * (b->m - m) + 2 * m * v1i) / (m + b->m) * b->friction;
					vx += dx * (v1f - v1i);
					vy += dy * (v1f - v1i);
					vz += dz * (v1f - v1i);
					b->vx += dx * (v2f - v2i);
					b->vy += dy * (v2f - v2i);
					b->vz += dz * (v2f - v2i);
					px += dx * (r + b->r - d) * b->m / (m + b->m);
					py += dy * (r + b->r - d) * b->m / (m + b->m);
					pz += dz * (r + b->r - d) * b->m / (m + b->m);
					b->px -= dx * (r + b->r - d) * m / (m + b->m);
					b->py -= dy * (r + b->r - d) * m / (m + b->m);
					b->pz -= dz * (r + b->r - d) * m / (m + b->m);
				}
			}
		}
	}

	void ball::advance(double dt) {
		physics();
		vx += ax * dt; vy += ay * dt; vz += az * dt;
		px += vx * dt; py += vy * dt; pz += vz * dt;
	}

	void ball::draw() {
		float colb0[4] = { 0.1, 0.3, 0.1, 1.0 };
		float colb1[4] = { 0.2, 0.5, 0.2, 1.0 };
		float colb2[4] = { 0.3, 0.6, 0.3, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colb0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colb1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colb2);

		glPushMatrix();
		glTranslated(px, py, pz);
		gluSphere(glsphere, r, 30, 30);
		glPopMatrix();
	}

	class cloth : public WorldObject {
	public:
		int dots, dotss, segs;
		double springacc, friction, stiffness, drag, dmass, colldist, thickness;
		int selfcollision, subdivision;
		float cola0[4];
		float cola1[4];
		float cola2[4];

		POINT3D* pp, * ppd, * pp2;
		VECTOR3D* pv, * pa, * pn, * pv2, * pa2;
		SPRING* pid;
		QUADTREE ct;

		cloth(int resolution, double length, double mass, double strength, double stiff, double thick) {
			dots = resolution + 1;
			dotss = dots * dots;
			segs = dotss * 2 + dots + (dots - 1) * (dots - 1) * 2;
			dmass = mass / dotss;
			springacc = strength / dmass;
			stiffness = stiff;
			thickness = thick / 2.0;
			friction = 0.3;
			drag = 0.99;
			selfcollision = FASTCOLLISION;
			colldist = 1.5 * length / resolution;
			subdivision = SUBDIVISION1;
			cola0[0] = 0.05; cola0[1] = 0.1;  cola0[2] = 0.3;  cola0[3] = 1.0;
			cola1[0] = 0.1;  cola1[1] = 0.2;  cola1[2] = 0.35; cola1[3] = 1.0;
			cola2[0] = 0.1;  cola2[1] = 0.25; cola2[2] = 0.4;  cola2[3] = 1.0;

			pp = new POINT3D[dotss];
			pv = new VECTOR3D[dotss];
			pa = new VECTOR3D[dotss];
			pn = new VECTOR3D[dotss * 4];
			ppd = new POINT3D[dotss * 4];
			pid = new SPRING[segs];
			pp2 = new POINT3D[dotss];
			pv2 = new VECTOR3D[dotss];
			pa2 = new VECTOR3D[dotss];

			buildtree(&ct, 0, 0, dots - 1, dots - 1);

			for (int i = 0; i < segs; i++) pid[i].id1 = pid[i].id2 = -1;

			double sqrt2 = sqrt(2.0);
			for (int i = 0; i < dots; i++)
				for (int j = 0; j < dots - 1; j++) {
					int sid = i * (dots - 1) + j;
					//
					pid[sid].id1 = i * dots + j;
					pid[sid].id2 = i * dots + j + 1;
					pid[sid].l = length / resolution;
					//
					sid = dotss + dots + j * dots + i;
					pid[sid].id1 = j * dots + i;
					pid[sid].id2 = j * dots + i + dots;
					pid[sid].l = length / resolution;
					if (i < dots - 1) {
						sid = dotss * 2 + dots + (i * (dots - 1) + j) * 2;
						//
						pid[sid].id1 = i * dots + j;
						pid[sid].id2 = i * dots + j + dots + 1;
						pid[sid].l = length / resolution * sqrt2;
						//
						pid[sid + 1].id1 = i * dots + j + 1;
						pid[sid + 1].id2 = i * dots + j + dots;
						pid[sid + 1].l = length / resolution * sqrt2;
					}
				}

			initialise(length / resolution);
		};

		~cloth() {
			delete[] pp;
			delete[] pv;
			delete[] pa;
			delete[] pn;
			delete[] ppd;
			delete[] pid;
			delete[] pp2;
			delete[] pv2;
			delete[] pa2;
		};

		void initialise(double ddist);
		int gettype() { return CLOTH; };
		void physics();
		void advance(double dt);
		void draw();

		void buildtree(QUADTREE* t, int x1, int y1, int x2, int y2) {
			t->x1 = x1;
			t->y1 = y1;
			t->x2 = x2;
			t->y2 = y2;
			if (x2 - x1 < 2 || y2 - y1 < 2) {
				t->tag = SUBDATA;
			}
			else {
				int xc = (x1 + x2) / 2;
				int yc = (y1 + y2) / 2;
				t->tag = SUBTREE;
				t->l1 = new QUADTREE;
				t->l2 = new QUADTREE;
				t->l3 = new QUADTREE;
				t->l4 = new QUADTREE;
				buildtree(t->l1, x1, y1, xc, yc);
				buildtree(t->l2, xc + 1, y1, x2, yc);
				buildtree(t->l3, x1, yc + 1, xc, y2);
				buildtree(t->l4, xc + 1, yc + 1, x2, y2);
			}
		}

		void updatetree(QUADTREE* t) {
			switch (t->tag) {
			case SUBDATA: {
				int idx = t->y1 * dots + t->x1;
				t->xa = t->xb = pp[idx].x;
				t->ya = t->yb = pp[idx].y;
				t->za = t->zb = pp[idx].z;
				for (int i = t->x1; i <= t->x2; i++)
					for (int j = t->y1; j <= t->y2; j++) {
						idx = j * dots + i;
						if (t->xa > pp[idx].x - colldist) t->xa = pp[idx].x - colldist;
						if (t->ya > pp[idx].y - colldist) t->ya = pp[idx].y - colldist;
						if (t->za > pp[idx].z - colldist) t->za = pp[idx].z - colldist;
						if (t->xb < pp[idx].x + colldist) t->xb = pp[idx].x + colldist;
						if (t->yb < pp[idx].y + colldist) t->yb = pp[idx].y + colldist;
						if (t->zb < pp[idx].z + colldist) t->zb = pp[idx].z + colldist;
					}
			}
						break;
			case SUBTREE:
				updatetree(t->l1);
				updatetree(t->l2);
				updatetree(t->l3);
				updatetree(t->l4);
				t->xa = min4(t->l1->xa, t->l2->xa, t->l3->xa, t->l4->xa);
				t->ya = min4(t->l1->ya, t->l2->ya, t->l3->ya, t->l4->ya);
				t->za = min4(t->l1->za, t->l2->za, t->l3->za, t->l4->za);
				t->xb = max4(t->l1->xb, t->l2->xb, t->l3->xb, t->l4->xb);
				t->yb = max4(t->l1->yb, t->l2->yb, t->l3->yb, t->l4->yb);
				t->zb = max4(t->l1->zb, t->l2->zb, t->l3->zb, t->l4->zb);
				break;
			}
		}

		void collidevertices(int xa1, int ya1, int xa2, int ya2, int xb1, int yb1, int xb2, int yb2) {
			for (int i1 = xa1; i1 <= xa2; i1++)
				for (int j1 = ya1; j1 <= ya2; j1++)
					for (int i2 = xb1; i2 <= xb2; i2++)
						for (int j2 = yb1; j2 <= yb2; j2++) {
							int i = j1 * dots + i1;
							int j = j2 * dots + i2;
							double d = (pp[i].x - pp[j].x) * (pp[i].x - pp[j].x) +
								(pp[i].y - pp[j].y) * (pp[i].y - pp[j].y) +
								(pp[i].z - pp[j].z) * (pp[i].z - pp[j].z);
							if (d < colldist * colldist) {
								double sqrt_d = sqrt(d);
								double dl = (colldist - sqrt_d) * 0.1 / sqrt_d * springacc;
								double ax = dl * (pp[j].x - pp[i].x);
								double ay = dl * (pp[j].y - pp[i].y);
								double az = dl * (pp[j].z - pp[i].z);
								pa[i].x -= ax; pa[i].y -= ay; pa[i].z -= az;
								pa[j].x += ax; pa[j].y += ay; pa[j].z += az;
							}
						}
		}

		void collidetree(QUADTREE* t) {
			switch (t->tag) {
				/*case SUBDATA:
				  collidevertices(t->x1, t->y1, t->x2, t->y2, t->x1, t->y1, t->x2, t->y2);
				break;*/
			case SUBTREE:
				collidetree(t->l1);
				collidetree(t->l2);
				collidetree(t->l3);
				collidetree(t->l4);
				collidetrees(t->l1, t->l2);
				collidetrees(t->l1, t->l3);
				collidetrees(t->l1, t->l4);
				collidetrees(t->l2, t->l3);
				collidetrees(t->l2, t->l4);
				collidetrees(t->l3, t->l4);
				break;
			}
		}

		void collidetrees(QUADTREE* t1, QUADTREE* t2) {
			if (t1->xa > t2->xb || t2->xa > t1->xb ||
				t1->ya > t2->yb || t2->ya > t1->yb ||
				t1->za > t2->zb || t2->za > t1->zb) return;
			if (t1->tag == SUBDATA || t2->tag == SUBDATA) {
				collidevertices(t1->x1, t1->y1, t1->x2, t1->y2, t2->x1, t2->y1, t2->x2, t2->y2);
			}
			else {
				collidetrees(t1->l1, t2->l1);
				collidetrees(t1->l1, t2->l2);
				collidetrees(t1->l1, t2->l3);
				collidetrees(t1->l1, t2->l4);
				collidetrees(t1->l2, t2->l1);
				collidetrees(t1->l2, t2->l2);
				collidetrees(t1->l2, t2->l3);
				collidetrees(t1->l2, t2->l4);
				collidetrees(t1->l3, t2->l1);
				collidetrees(t1->l3, t2->l2);
				collidetrees(t1->l3, t2->l3);
				collidetrees(t1->l3, t2->l4);
				collidetrees(t1->l4, t2->l1);
				collidetrees(t1->l4, t2->l2);
				collidetrees(t1->l4, t2->l3);
				collidetrees(t1->l4, t2->l4);
			}
		}

		void collidevertices2(int xa1, int ya1, int xa2, int ya2, int xb1, int yb1, int xb2, int yb2, cloth* c1, cloth* c2) {
			for (int i1 = xa1; i1 <= xa2; i1++)
				for (int j1 = ya1; j1 <= ya2; j1++)
					for (int i2 = xb1; i2 <= xb2; i2++)
						for (int j2 = yb1; j2 <= yb2; j2++) {
							int i = j1 * c1->dots + i1;
							int j = j2 * c2->dots + i2;
							double d = (c1->pp[i].x - c2->pp[j].x) * (c1->pp[i].x - c2->pp[j].x) +
								(c1->pp[i].y - c2->pp[j].y) * (c1->pp[i].y - c2->pp[j].y) +
								(c1->pp[i].z - c2->pp[j].z) * (c1->pp[i].z - c2->pp[j].z);
							if (d < colldist * colldist * 1.5) {
								double sqrt_d = sqrt(d);
								double dl = (colldist * sqrt(1.5) - sqrt_d) * 0.1 / sqrt_d * springacc;
								double ax = dl * (c2->pp[j].x - c1->pp[i].x);
								double ay = dl * (c2->pp[j].y - c1->pp[i].y);
								double az = dl * (c2->pp[j].z - c1->pp[i].z);
								c1->pa[i].x -= ax; c1->pa[i].y -= ay; c1->pa[i].z -= az;
								c2->pa[j].x += ax; c2->pa[j].y += ay; c2->pa[j].z += az;
							}
						}
		}

		void collidetrees2(QUADTREE* t1, QUADTREE* t2, cloth* c1, cloth* c2) {
			if (t1->xa > t2->xb || t2->xa > t1->xb ||
				t1->ya > t2->yb || t2->ya > t1->yb ||
				t1->za > t2->zb || t2->za > t1->zb) return;
			if (t1->tag == SUBDATA || t2->tag == SUBDATA) {
				collidevertices2(t1->x1, t1->y1, t1->x2, t1->y2, t2->x1, t2->y1, t2->x2, t2->y2, c1, c2);
			}
			else {
				collidetrees2(t1->l1, t2->l1, c1, c2);
				collidetrees2(t1->l1, t2->l2, c1, c2);
				collidetrees2(t1->l1, t2->l3, c1, c2);
				collidetrees2(t1->l1, t2->l4, c1, c2);
				collidetrees2(t1->l2, t2->l1, c1, c2);
				collidetrees2(t1->l2, t2->l2, c1, c2);
				collidetrees2(t1->l2, t2->l3, c1, c2);
				collidetrees2(t1->l2, t2->l4, c1, c2);
				collidetrees2(t1->l3, t2->l1, c1, c2);
				collidetrees2(t1->l3, t2->l2, c1, c2);
				collidetrees2(t1->l3, t2->l3, c1, c2);
				collidetrees2(t1->l3, t2->l4, c1, c2);
				collidetrees2(t1->l4, t2->l1, c1, c2);
				collidetrees2(t1->l4, t2->l2, c1, c2);
				collidetrees2(t1->l4, t2->l3, c1, c2);
				collidetrees2(t1->l4, t2->l4, c1, c2);
			}
		}

	};

	void cloth::initialise(double ddist) {
		for (int i = 0; i < dots; i++)
			for (int j = 0; j < dots; j++) {
				pp[i * dots + j].x = j * ddist - (dots - 1) * ddist / 2;
				pp[i * dots + j].y = (dots - 1) * ddist;
				pp[i * dots + j].z = (dots - 1) * ddist / 2 - i * ddist;
				pp[i * dots + j].fixed = 0;
				pv[i * dots + j].x = pv[i * dots + j].y = pv[i * dots + j].z = 0.0;
				pa[i * dots + j].x = pa[i * dots + j].y = pa[i * dots + j].z = 0.0;
			}
		pp[0].fixed = 1;
		pp[dots - 1].fixed = 1;
		pp[dotss - 1].fixed = 1;
		pp[dotss - dots].fixed = 1;
	}

	void cloth::physics() {
		int i, j, c, id1, id2;
		double d, dl, ax, ay, az, l, sl;

		for (i = 0; i < dotss; i++) {
			pa[i].x = 0;
			pa[i].y = -gravity;
			pa[i].z = 0;
		}

		for (i = 0; i < segs; i++) {
			id1 = pid[i].id1;
			id2 = pid[i].id2;
			l = pid[i].l;
			sl = l * stiffness;
			if (id1 != -1 && id2 != -1) {
				ax = pp[id2].x - pp[id1].x;
				ay = pp[id2].y - pp[id1].y;
				az = pp[id2].z - pp[id1].z;
				d = sqrt(ax * ax + ay * ay + az * az);
				if (d > sl) {
					switch (pp[id1].fixed + pp[id2].fixed * 2) {
					case 0:
						dl = (d - l) / 2 / d;
						pp[id1].x += ax * dl; pp[id1].y += ay * dl; pp[id1].z += az * dl;
						pv[id1].x += ax * dl; pv[id1].y += ay * dl; pv[id1].z += az * dl;
						pa[id1].x += ax * dl; pa[id1].y += ay * dl; pa[id1].z += az * dl;
						pp[id2].x -= ax * dl; pp[id2].y -= ay * dl; pp[id2].z -= az * dl;
						pv[id2].x -= ax * dl; pv[id2].y -= ay * dl; pv[id2].z -= az * dl;
						pa[id2].x -= ax * dl; pa[id2].y -= ay * dl; pa[id2].z -= az * dl;
						break;
					case 1:
						dl = (d - l) / d;
						pp[id2].x -= ax * dl; pp[id2].y -= ay * dl; pp[id2].z -= az * dl;
						pv[id2].x -= ax * dl; pv[id2].y -= ay * dl; pv[id2].z -= az * dl;
						pa[id2].x -= ax * dl; pa[id2].y -= ay * dl; pa[id2].z -= az * dl;
						break;
					case 2:
						dl = (d - l) / d;
						pp[id1].x += ax * dl; pp[id1].y += ay * dl; pp[id1].z += az * dl;
						pv[id1].x += ax * dl; pv[id1].y += ay * dl; pv[id1].z += az * dl;
						pa[id1].x += ax * dl; pa[id1].y += ay * dl; pa[id1].z += az * dl;
						break;
					}
				}
				if (d > l) dl = (d - l) / d * springacc; else dl = 0;
				ax = (pv[id2].x - pv[id1].x) * friction + dl * ax;
				ay = (pv[id2].y - pv[id1].y) * friction + dl * ay;
				az = (pv[id2].z - pv[id1].z) * friction + dl * az;
				pa[id1].x += ax; pa[id1].y += ay; pa[id1].z += az;
				pa[id2].x -= ax; pa[id2].y -= ay; pa[id2].z -= az;
			}
		}

		switch (selfcollision) {
		case NOCOLLISION:
			break;

		case FASTCOLLISION:
			updatetree(&ct);
			collidetree(&ct);
			break;
		}

		int ind = 0;
		for (j = 0; j < OBJECTS; j++) {
			if (obj[j] == this) ind = 1;
			switch (obj[j]->gettype()) {
			case BALL: {
				ball* b = (ball*)obj[j];
				for (i = 0; i < dotss; i++) {
					pp[i].x -= b->px;
					pp[i].y -= b->py;
					pp[i].z -= b->pz;
					d = sqrt(pp[i].x * pp[i].x + pp[i].y * pp[i].y + pp[i].z * pp[i].z);
					if (d < b->r) {
						pp[i].x /= d;
						pp[i].y /= d;
						pp[i].z /= d;
						double v1i = pp[i].x * pv[i].x + pp[i].y * pv[i].y + pp[i].z * pv[i].z;
						double v2i = pp[i].x * b->vx + pp[i].y * b->vy + pp[i].z * b->vz;
						if (v1i < v2i) {
							double v1f = (v1i * (dmass - b->m) + 2 * b->m * v2i) / (dmass + b->m);
							double v2f = (v2i * (b->m - dmass) + 2 * dmass * v1i) / (dmass + b->m);
							if (v1f > v2f) {
								pv[i].x += pp[i].x * (v1f - v1i);
								pv[i].y += pp[i].y * (v1f - v1i);
								pv[i].z += pp[i].z * (v1f - v1i);
								pa[i].x += pp[i].x * (v1f - v1i);
								pa[i].y += pp[i].y * (v1f - v1i);
								pa[i].z += pp[i].z * (v1f - v1i);
								pv[i].x *= b->friction;
								pv[i].y *= b->friction;
								pv[i].z *= b->friction;
								b->vx += pp[i].x * (v2f - v2i);
								b->vy += pp[i].y * (v2f - v2i);
								b->vz += pp[i].z * (v2f - v2i);
								b->ax += pp[i].x * (v2f - v2i);
								b->ay += pp[i].y * (v2f - v2i);
								b->az += pp[i].z * (v2f - v2i);
							}
						}
						pp[i].x *= b->r;
						pp[i].y *= b->r;
						pp[i].z *= b->r;
					}
					pp[i].x += b->px;
					pp[i].y += b->py;
					pp[i].z += b->pz;
				}
			}
					 break;
			case CLOTH: {
				cloth* c = (cloth*)obj[j];
				if (ind && c != this && selfcollision != NOCOLLISION && c->selfcollision != NOCOLLISION)
					collidetrees2(&ct, &(c->ct), this, c);
			}
					  break;
			}
		}

		for (i = 0; i < dotss; i++) {
			if (pp[i].fixed != 0) {
				pv[i].x = pv[i].y = pv[i].z = 0;
				pa[i].x = pa[i].y = pa[i].z = 0;
			}
			pv[i].x *= drag;
			pv[i].y *= drag;
			pv[i].z *= drag;
			if (pp[i].y < 0.0) {
				pv[i].y *= -0.1;
				pv[i].x *= 0.7;
				pv[i].z *= 0.7;
				pp[i].y = 0.0;
			}
		}

		for (i = segs - 1; i >= 0; i--) {
			id1 = pid[i].id1;
			id2 = pid[i].id2;
			l = pid[i].l;
			sl = l * stiffness;
			if (id1 != -1 && id2 != -1) {
				ax = pp[id2].x - pp[id1].x;
				ay = pp[id2].y - pp[id1].y;
				az = pp[id2].z - pp[id1].z;
				d = sqrt(ax * ax + ay * ay + az * az);
				if (d > sl) {
					switch (pp[id1].fixed + pp[id2].fixed * 2) {
					case 0:
						dl = (d - l) / 2 / d;
						pp[id1].x += ax * dl; pp[id1].y += ay * dl; pp[id1].z += az * dl;
						pv[id1].x += ax * dl; pv[id1].y += ay * dl; pv[id1].z += az * dl;
						pa[id1].x += ax * dl; pa[id1].y += ay * dl; pa[id1].z += az * dl;
						pp[id2].x -= ax * dl; pp[id2].y -= ay * dl; pp[id2].z -= az * dl;
						pv[id2].x -= ax * dl; pv[id2].y -= ay * dl; pv[id2].z -= az * dl;
						pa[id2].x -= ax * dl; pa[id2].y -= ay * dl; pa[id2].z -= az * dl;
						break;
					case 1:
						dl = (d - l) / d;
						pp[id2].x -= ax * dl; pp[id2].y -= ay * dl; pp[id2].z -= az * dl;
						pv[id2].x -= ax * dl; pv[id2].y -= ay * dl; pv[id2].z -= az * dl;
						pa[id2].x -= ax * dl; pa[id2].y -= ay * dl; pa[id2].z -= az * dl;
						break;
					case 2:
						dl = (d - l) / d;
						pp[id1].x += ax * dl; pp[id1].y += ay * dl; pp[id1].z += az * dl;
						pv[id1].x += ax * dl; pv[id1].y += ay * dl; pv[id1].z += az * dl;
						pa[id1].x += ax * dl; pa[id1].y += ay * dl; pa[id1].z += az * dl;
						break;
					}
				}
			}
		}

	}

	void cloth::advance(double dt) {
		dt *= 0.5;
		physics();
		pp2 = pp;
		pv2 = pv;
		pa2 = pa;
		for (int i = 0; i < dotss; i++) {
			pv[i].x += pa[i].x * dt;
			pv[i].y += pa[i].y * dt;
			pv[i].z += pa[i].z * dt;
			pp[i].x += pv[i].x * dt;
			pp[i].y += pv[i].y * dt;
			pp[i].z += pv[i].z * dt;
		}
		physics();
		for (int i = 0; i < dotss; i++) {
			pv[i].x = pv2[i].x + (pa[i].x + pa2[i].x) * dt;
			pv[i].y = pv2[i].y + (pa[i].y + pa2[i].y) * dt;
			pv[i].z = pv2[i].z + (pa[i].z + pa2[i].z) * dt;
			pp[i].x = pp2[i].x + (pv[i].x + pv2[i].x) * dt;
			pp[i].y = pp2[i].y + (pv[i].y + pv2[i].y) * dt;
			pp[i].z = pp2[i].z + (pv[i].z + pv2[i].z) * dt;
		}
	}

	void cloth::draw() {
		int i, j, cpid;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cola0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cola1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cola2);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 2);

		switch (subdivision) {

		case NOSUBDIVISION:
			for (i = 0; i < dots; i++)
				for (j = 0; j < dots; j++) {
					cpid = i * dots + j;
					if (i < dots - 1) {
						if (j < dots - 1) {
							normalv(pp[cpid], pp[cpid + 1], pp[cpid + dots], pn[cpid]);
						}
						else {
							normalv(pp[cpid], pp[cpid + dots], pp[cpid - 1], pn[cpid]);
						}
					}
					else {
						if (j < dots - 1) {
							normalv(pp[cpid], pp[cpid - dots], pp[cpid + 1], pn[cpid]);
						}
						else {
							normalv(pp[cpid], pp[cpid - 1], pp[cpid - dots], pn[cpid]);
						}
					}
				}

			glDisable(GL_CULL_FACE);
			glBegin(GL_QUADS);
			for (i = 0; i < dots - 1; i++) {
				for (j = 0; j < dots - 1; j++) {
					cpid = i * dots + j;
					glNormal3d(pn[cpid].x, pn[cpid].y, pn[cpid].z);
					glVertex3d(pp[cpid].x, pp[cpid].y, pp[cpid].z);
					cpid++;
					glNormal3d(pn[cpid].x, pn[cpid].y, pn[cpid].z);
					glVertex3d(pp[cpid].x, pp[cpid].y, pp[cpid].z);
					cpid += dots;
					glNormal3d(pn[cpid].x, pn[cpid].y, pn[cpid].z);
					glVertex3d(pp[cpid].x, pp[cpid].y, pp[cpid].z);
					cpid--;
					glNormal3d(pn[cpid].x, pn[cpid].y, pn[cpid].z);
					glVertex3d(pp[cpid].x, pp[cpid].y, pp[cpid].z);
				}
			}
			glEnd();
			glEnable(GL_CULL_FACE);
			break;

		case SUBDIVISION1:
			int dots2 = dots * 2;

			for (i = 0; i < dots; i++)
				for (j = 0; j < dots; j++) {
					cpid = i * dots + j;
					ppd[i * dots2 * 2 + j * 2].x = pp[cpid].x;
					ppd[i * dots2 * 2 + j * 2].y = pp[cpid].y;
					ppd[i * dots2 * 2 + j * 2].z = pp[cpid].z;
				}
			for (i = 0; i < dots - 1; i++)
				for (j = 0; j < dots - 1; j++) {
					cpid = i * dots2 * 2 + j * 2 + 1 + dots2;
					ppd[cpid].x = 0.25 * (ppd[cpid - 1 - dots2].x + ppd[cpid + 1 - dots2].x
						+ ppd[cpid - 1 + dots2].x + ppd[cpid + 1 + dots2].x);
					ppd[cpid].y = 0.25 * (ppd[cpid - 1 - dots2].y + ppd[cpid + 1 - dots2].y
						+ ppd[cpid - 1 + dots2].y + ppd[cpid + 1 + dots2].y);
					ppd[cpid].z = 0.25 * (ppd[cpid - 1 - dots2].z + ppd[cpid + 1 - dots2].z
						+ ppd[cpid - 1 + dots2].z + ppd[cpid + 1 + dots2].z);
				}
			for (i = 0; i < dots; i++)
				for (j = 0; j < dots - 1; j++) {
					cpid = i * dots2 * 2 + j * 2 + 1;
					if (i == 0) {
						ppd[cpid].x = 0.5 * (ppd[cpid - 1].x + ppd[cpid + 1].x);
						ppd[cpid].y = 0.5 * (ppd[cpid - 1].y + ppd[cpid + 1].y);
						ppd[cpid].z = 0.5 * (ppd[cpid - 1].z + ppd[cpid + 1].z);
					}
					else if (i == dots - 1) {
						ppd[cpid].x = 0.5 * (ppd[cpid - 1].x + ppd[cpid + 1].x);
						ppd[cpid].y = 0.5 * (ppd[cpid - 1].y + ppd[cpid + 1].y);
						ppd[cpid].z = 0.5 * (ppd[cpid - 1].z + ppd[cpid + 1].z);
					}
					else {
						ppd[cpid].x = 0.25 * (ppd[cpid + dots2].x + ppd[cpid - dots2].x +
							ppd[cpid - 1].x + ppd[cpid + 1].x);
						ppd[cpid].y = 0.25 * (ppd[cpid + dots2].y + ppd[cpid - dots2].y +
							ppd[cpid - 1].y + ppd[cpid + 1].y);
						ppd[cpid].z = 0.25 * (ppd[cpid + dots2].z + ppd[cpid - dots2].z +
							ppd[cpid - 1].z + ppd[cpid + 1].z);
					}
					cpid = j * dots2 * 2 + i * 2 + dots2;
					if (i == 0) {
						ppd[cpid].x = 0.5 * (ppd[cpid - dots2].x + ppd[cpid + dots2].x);
						ppd[cpid].y = 0.5 * (ppd[cpid - dots2].y + ppd[cpid + dots2].y);
						ppd[cpid].z = 0.5 * (ppd[cpid - dots2].z + ppd[cpid + dots2].z);
					}
					else if (i == dots - 1) {
						ppd[cpid].x = 0.5 * (ppd[cpid - dots2].x + ppd[cpid + dots2].x);
						ppd[cpid].y = 0.5 * (ppd[cpid - dots2].y + ppd[cpid + dots2].y);
						ppd[cpid].z = 0.5 * (ppd[cpid - dots2].z + ppd[cpid + dots2].z);
					}
					else {
						ppd[cpid].x = 0.25 * (ppd[cpid + dots2].x + ppd[cpid - dots2].x +
							ppd[cpid - 1].x + ppd[cpid + 1].x);
						ppd[cpid].y = 0.25 * (ppd[cpid + dots2].y + ppd[cpid - dots2].y +
							ppd[cpid - 1].y + ppd[cpid + 1].y);
						ppd[cpid].z = 0.25 * (ppd[cpid + dots2].z + ppd[cpid - dots2].z +
							ppd[cpid - 1].z + ppd[cpid + 1].z);
					}
				}
			for (i = 1; i < dots - 1; i++) {
				cpid = i * 2;
				ppd[cpid].x = 0.5 * ppd[cpid].x + 0.25 * (ppd[cpid - 1].x + ppd[cpid + 1].x);
				ppd[cpid].y = 0.5 * ppd[cpid].y + 0.25 * (ppd[cpid - 1].y + ppd[cpid + 1].y);
				ppd[cpid].z = 0.5 * ppd[cpid].z + 0.25 * (ppd[cpid - 1].z + ppd[cpid + 1].z);
				cpid = dots2 * dots2 - dots2 - 2 - i * 2;
				ppd[cpid].x = 0.5 * ppd[cpid].x + 0.25 * (ppd[cpid - 1].x + ppd[cpid + 1].x);
				ppd[cpid].y = 0.5 * ppd[cpid].y + 0.25 * (ppd[cpid - 1].y + ppd[cpid + 1].y);
				ppd[cpid].z = 0.5 * ppd[cpid].z + 0.25 * (ppd[cpid - 1].z + ppd[cpid + 1].z);
				cpid = i * dots2 * 2;
				ppd[cpid].x = 0.5 * ppd[cpid].x + 0.25 * (ppd[cpid - dots2].x + ppd[cpid + dots2].x);
				ppd[cpid].y = 0.5 * ppd[cpid].y + 0.25 * (ppd[cpid - dots2].y + ppd[cpid + dots2].y);
				ppd[cpid].z = 0.5 * ppd[cpid].z + 0.25 * (ppd[cpid - dots2].z + ppd[cpid + dots2].z);
				cpid = i * dots2 * 2 + dots2 - 2;
				ppd[cpid].x = 0.5 * ppd[cpid].x + 0.25 * (ppd[cpid - dots2].x + ppd[cpid + dots2].x);
				ppd[cpid].y = 0.5 * ppd[cpid].y + 0.25 * (ppd[cpid - dots2].y + ppd[cpid + dots2].y);
				ppd[cpid].z = 0.5 * ppd[cpid].z + 0.25 * (ppd[cpid - dots2].z + ppd[cpid + dots2].z);
			}
			for (i = 1; i < dots - 1; i++) {
				for (j = 1; j < dots - 1; j++) {
					cpid = i * dots2 * 2 + j * 2;
					ppd[cpid].x = 0.5 * ppd[cpid].x + 0.0625 *
						(ppd[cpid - dots2 - 1].x + ppd[cpid - dots2].x + ppd[cpid - dots2 + 1].x +
							ppd[cpid + dots2 - 1].x + ppd[cpid + dots2].x + ppd[cpid + dots2 + 1].x +
							ppd[cpid - 1].x + ppd[cpid + 1].x);
					ppd[cpid].y = 0.5 * ppd[cpid].y + 0.0625 *
						(ppd[cpid - dots2 - 1].y + ppd[cpid - dots2].y + ppd[cpid - dots2 + 1].y +
							ppd[cpid + dots2 - 1].y + ppd[cpid + dots2].y + ppd[cpid + dots2 + 1].y +
							ppd[cpid - 1].y + ppd[cpid + 1].y);
					ppd[cpid].z = 0.5 * ppd[cpid].z + 0.0625 *
						(ppd[cpid - dots2 - 1].z + ppd[cpid - dots2].z + ppd[cpid - dots2 + 1].z +
							ppd[cpid + dots2 - 1].z + ppd[cpid + dots2].z + ppd[cpid + dots2 + 1].z +
							ppd[cpid - 1].z + ppd[cpid + 1].z);
				}
			}
			cpid = dots2 * dots2 - dots2 - 2;
			normalv(ppd[cpid], ppd[cpid - 1], ppd[cpid - dots2], pn[cpid]);
			double lgt = sqrt(pn[cpid].x * pn[cpid].x + pn[cpid].y * pn[cpid].y + pn[cpid].z * pn[cpid].z);
			pn[cpid].x /= lgt;
			pn[cpid].y /= lgt;
			pn[cpid].z /= lgt;
			for (i = 0; i < dots2 - 2; i++) {
				cpid = i * dots2 + dots2 - 2;
				normalv(ppd[cpid], ppd[cpid + dots2], ppd[cpid - 1], pn[cpid]);
				lgt = sqrt(pn[cpid].x * pn[cpid].x + pn[cpid].y * pn[cpid].y + pn[cpid].z * pn[cpid].z);
				pn[cpid].x /= lgt;
				pn[cpid].y /= lgt;
				pn[cpid].z /= lgt;
				cpid = (dots2 - 2) * dots2 + i;
				normalv(ppd[cpid], ppd[cpid - dots2], ppd[cpid + 1], pn[cpid]);
				lgt = sqrt(pn[cpid].x * pn[cpid].x + pn[cpid].y * pn[cpid].y + pn[cpid].z * pn[cpid].z);
				pn[cpid].x /= lgt;
				pn[cpid].y /= lgt;
				pn[cpid].z /= lgt;
			}
			for (i = 0; i < dots2 - 2; i++)
				for (j = 0; j < dots2 - 2; j++) {
					cpid = i * dots2 + j;
					normalv(ppd[cpid], ppd[cpid + 1], ppd[cpid + dots2], pn[cpid]);
					lgt = sqrt(pn[cpid].x * pn[cpid].x + pn[cpid].y * pn[cpid].y + pn[cpid].z * pn[cpid].z);
					pn[cpid].x /= lgt;
					pn[cpid].y /= lgt;
					pn[cpid].z /= lgt;
				}

			glBegin(GL_QUADS);
			for (int i = 0; i < dots2 - 2; i++) {
				int ptid = i;
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				ptid++;
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				ptid = dots2 * dots2 - dots2 - 2 - i;
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				ptid--;
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				ptid = dots2 * i;
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				ptid += dots2;
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				ptid = dots2 * i + dots2 - 2;
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				ptid += dots2;
				glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
				glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
				glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
				glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
			}
			for (int i = 0; i < dots2 - 2; i++) {
				for (int j = 0; j < dots2 - 2; j++) {
					int ptid = i * dots2 + j;
					glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
					glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
					ptid += dots2;
					glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
					glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
					ptid++;
					glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
					glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
					ptid -= dots2;
					glNormal3d(-pn[ptid].x, -pn[ptid].y, -pn[ptid].z);
					glVertex3d(ppd[ptid].x - pn[ptid].x * thickness, ppd[ptid].y - pn[ptid].y * thickness, ppd[ptid].z - pn[ptid].z * thickness);
					ptid--;
					glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
					glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
					ptid++;
					glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
					glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
					ptid += dots2;
					glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
					glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
					ptid--;
					glNormal3d(pn[ptid].x, pn[ptid].y, pn[ptid].z);
					glVertex3d(ppd[ptid].x + pn[ptid].x * thickness, ppd[ptid].y + pn[ptid].y * thickness, ppd[ptid].z + pn[ptid].z * thickness);
				}
			}
			glEnd();
			break;
		}

	}

	void drawText(float x, float y, std::string text)
	{
		glRasterPos2f(x, y);
		glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
	}

	//Отрисовка окна
	void display() {
		//Очистка экрана и установка начальных значений
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camx, camy, camz, camx + viewx, camy + viewy, camz + viewz, 0, 1, 0);

		

		//Отрисовка пола
		float colb0[4] = { 0.6, 0.6, 0.63, 1.0 };
		float colb1[4] = { 0.7, 0.7, 0.75, 1.0 };
		float colb2[4] = { 0.9, 0.9, 0.94, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colb0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colb1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colb2);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

		glBegin(GL_QUADS);
		glNormal3d(0.0, -1.0, 0.0);
		glVertex3d(-100.0, 0.0, -100.0);
		glVertex3d(-100.0, 0.0, 100.0);
		glVertex3d(100.0, 0.0, 100.0);
		glVertex3d(100.0, 0.0, -100.0);
		glEnd();

		//Отрисовка объектов
		for (int i = 0; i < OBJECTS; i++) obj[i]->draw();


		glOrtho(-10 * aspect_ratio, 10 * aspect_ratio, -10, 10, -1, 1);
		glColor3ub(0, 255, 255);

		drawText(-14, 4, "KDZ 2. Variant 4. A Cloth and a ball.\nKharchenko Artem BSE161\nKey 'R':Start the cloth falling\nKey 'S':Start again\nKey 'L':Turn on\\off the ligth\nKeys up and down:Camera control\n");

		glutSwapBuffers();
	}

	void movecam(double fwd, double strafe) {
		double spd = 1.0 / sqrt(viewx * viewx + viewy * viewy + viewz * viewz);
		camx += (viewx * fwd - viewz * strafe) * spd;
		camy += (viewy * fwd) * spd;
		camz += (viewz * fwd + viewx * strafe) * spd;
	}

	void advanceall(double dt) {
		for (int i = 0; i < OBJECTS; i++) obj[i]->advance(dt);
	}

	//Происходит при простаивании
	void idle() {
		advanceall(time_step);
		glutPostRedisplay();
	}

	//Координаты мыши
	int mousex = -0x10000, mousey;

	//При зажимании левой кнопки мыши
	void mouse(int button, int state, int x, int y) {
		//Сбросить статус
		mousex = -0x10000;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			mousex = x;
			mousey = y;
		}
	}

	//Поворот камеры
	void rotate2d(double ang, double& x, double& y) {
		double cos_a = cos(ang), sin_a = sin(ang);
		double xr = x * cos_a - y * sin_a;
		double yr = x * sin_a + y * cos_a;
		x = xr;
		y = yr;
	}

	//Передвижение мыши
	void motion(int x, int y) {
		if (mousex != -0x10000) {
			double mdx = (x - mousex) * -0.01;
			double mdy = (y - mousey) * -0.01;
			double xang = atan2(viewx, viewz);
			rotate2d(xang, viewx, viewz);
			rotate2d(mdy, viewz, viewy);
			rotate2d(-xang - mdx, viewx, viewz);
		}
		mousex = x;
		mousey = y;
	}

	//Перезагрузка объектов
	void reloadobj()
	{
		obj[0] = new cloth(25, 1.0, 15.0, 350.0, 1.05, 0.05);
		obj[1] = new ball(0.0, 0.0, 0.0, 0.2, 10.0, 0.0, 0.9);
	}

	//Действия на кнопки
	void key(unsigned char k, int x, int y) {
		switch (k) {
		case 27: exit(0);
		case 'r': case 'R': {
			int ds = ((cloth*)obj[0])->dots;
			((cloth*)obj[0])->pp[0].fixed = 0;
			((cloth*)obj[0])->pp[ds - 1].fixed = 0;
			((cloth*)obj[0])->pp[ds * ds - 1].fixed = 0;
			((cloth*)obj[0])->pp[ds * (ds - 1)].fixed = 0;
			((cloth*)obj[0])->pp[ds * (ds / 3)].fixed = 0;
			((cloth*)obj[0])->pp[ds * (ds / 3) - ds / 3].fixed = 0;
		}
				break;
		case 'l': case 'L': {
			light_switch = !light_switch;
			light_switch ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
			break;
		}
		case 's': case 'S': {
			reloadobj();
			break;
		}
				
		}
	}

	void special(int key, int x, int y) {
		switch (key) {
		case GLUT_KEY_UP: movecam(camspeed, 0.0); break;
		case GLUT_KEY_DOWN: movecam(-camspeed, 0.0); break;
		case GLUT_KEY_LEFT: movecam(0.0, -camspeed); break;
		case GLUT_KEY_RIGHT: movecam(0.0, camspeed); break;
		case GLUT_KEY_PAGE_UP: camy += camspeed; break;
		case GLUT_KEY_PAGE_DOWN: camy -= camspeed; break;
		}
	}

	//При изменения размеров
	void reshape(int w, int h) {
		if (h == 0) h = 1;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		aspect_ratio = (double)w / (double)h;
		glViewport(0, 0, w, h);
		gluPerspective(45, double(w) / h, 0.01, 100.0);
	}

	
}

//Начальная точка
int main(int argc, char* argv[]) {

	//Инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Cloth and Ball");

	//Добавление методов
	glutDisplayFunc(KDZ2::display);
	glutIdleFunc(KDZ2::idle);
	glutMouseFunc(KDZ2::mouse);
	glutMotionFunc(KDZ2::motion);
	glutReshapeFunc(KDZ2::reshape);
	glutKeyboardFunc(KDZ2::key);
	glutSpecialFunc(KDZ2::special);

	//Источники света
	float pos[4] = { 0, 0, 1, 0 };
	float Ia[4] = { 1.0, 1.0, 1.0, 1.0 }, Id[4] = { 0.5, 0.5, 0.5, 1.0 }, Is[4] = { 1, 1, 1, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ia);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Id);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Is);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//Размеры
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Матрица
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.0, 0.01, 100.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	//Добавление объектов
	KDZ2::reloadobj();

	glutMainLoop();
}