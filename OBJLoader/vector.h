#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

class Vector {
private:
	float x,y,z,a;
public:
	Vector() { x=0.0; y=0.0; z=0.0; a=0.0; }
	Vector(float _x, float _y) { x=_x; y=_y; z=1.0; a=1.0; } // for textures
	Vector(float _x, float _y, float _z) { x=_x; y=_y; z=_z; a=1.0; } // for vertices
	Vector(float _x, float _y, float _z, float _a) { x=_x; y=_y; z=_z; a=_a; } // for colours
	float getx() const { return x; }
	float gety() const { return y; }
	float getz() const { return z; }
	float geta() const { return a; }
};

ostream& operator<<(ostream& out, Vector v);

#endif