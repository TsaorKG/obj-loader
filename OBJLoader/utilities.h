#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include "vector.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

using namespace std;

vector<string> split(const string& line, char c);
string getMtlFilename(const string& line); // special function to get MTL filename
int index(vector<string> v, string s);
void VectorTOglfloat(Vector v, GLfloat* tmp);
bool exist(const string& name); // test existence of a file


#endif