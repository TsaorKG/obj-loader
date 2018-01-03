#include "utilities.h"
#include "vector.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

using namespace std;


vector<string> split(const string& line, char c) {
	// Return a vector of strings that were separated by the character c in line
	vector<string> v_strings;
	stringstream ss(line);
	string item;
	while (getline(ss, item, c)) {
		if (item[0] != 'v' && item[0] != 'f' && item[0] != 'm' && item[0] != 'u' && item[0] != 'n' && item[0] != 'N' && item[0] != 'K' && item[0] != 'm') {
			if (c == ' ' && item.size() != 0) {
				v_strings.push_back(item);
			}
			if (c == '/') { // with '/' we want to keep void elements
				v_strings.push_back(item);
			}
		}
	}
	return v_strings;
}

string getMtlFilename(const string& line) {
	// special function to get MTL filename
	stringstream ss(line);
	string item;
	getline(ss, item, ' '); // mtllib
	getline(ss, item, ' '); // filename
	if (item[item.size()-1] == '\r') { // get rid of windows end-of-line character
		item = item.substr(0,item.size()-1);
	}
	return item;
}

int index(vector<string> v, string s) {
	// Find the index of first occurence of s into the string vector v
	for (int i=0; i<v.size(); i++) {
		if (v[i] == s) { return i; }
	}
	return -1;
}

void VectorTOglfloat(Vector v, GLfloat* tmp) {
	tmp[0] = (GLfloat)v.getx();
	tmp[1] = (GLfloat)v.gety();
	tmp[2] = (GLfloat)v.getz();
}

bool exist(const string& name) {
	// test existence of a file
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	return false;
}
