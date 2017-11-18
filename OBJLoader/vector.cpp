#include "vector.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, Vector v) {
	out << "(" << v.getx() << "," << v.gety() << "," << v.getz() << "," << v.geta() << ")" << endl;
	return out;
}