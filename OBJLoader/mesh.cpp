#include "vector.h"
#include "mesh.h"
#include "utilities.h"
#include <fstream>
#include <iostream>
#include "stdlib.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

using namespace std;

void Mesh::readOBJ(const char* filename) {
	// Read an OBJ file (filename) and retrieve all the vertices coordinates
	ifstream infile (filename); // open the file in reading mode
	string line;
	if (infile.is_open()) {
		while (getline(infile, line)) {
			if (line[0] == 'v') { // vertices and normals management
				vector<string> v = split(line, ' ');
				if (line[1] == 'n') { // add vectors to normals list, converting strings to floats
					normals.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str()),atof(v[2].c_str())));
				}
				if (line[1] == 't') {
					textures.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str())));
				}
				else { // add vectors to vertices list, converting strings to floats
					vertices.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str()),atof(v[2].c_str())));
				}
			}
			if (line[0] == 'f') { // faces management
				vector<int> faces_v_tmp, faces_t_tmp, faces_n_tmp;
				vector<string> v = split(line, ' '); // split the line at the spaces
				for (int i=0; i<v.size(); i++) {
					vector<string> v2 = split(v[i], '/'); // split the string at the slashes
					faces_v_tmp.push_back(atoi(v2[0].c_str())-1);
					// condition ? value_if_true : value_if_false
					// in case there is no texture data we put "1"
					faces_t_tmp.push_back( atoi(((v2[1].size()==0)?"1":v2[1]).c_str()) -1);
					faces_n_tmp.push_back(atoi(v2[2].c_str())-1);
				}
				faces_v.push_back(faces_v_tmp);
				faces_t.push_back(faces_t_tmp);
				faces_n.push_back(faces_n_tmp);

			}
		}
		infile.close();
		nbFaces = faces_v.size();
		nbVertices = vertices.size();
		nbNormals = normals.size();
	}
}

GLvoid Mesh::affichage() const {
	// Emptying frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); // projection?

	// Rotation
   glLoadIdentity();
   glRotatef(-angleY,1.0f,0.0f,0.0f);
   glRotatef(-angleX,0.0f,1.0f,0.0f);
   glScalef(zoom,zoom,zoom);

	// Draw a face at a time
	for(int i=0;i<nbFaces;i++) {
	  glBegin(GL_POLYGON);
	  for(int j=0;j<faces_v[i].size();j++) {
	     //glColor3f(1.0,0.5,0.5);
	     glVertex3f(vertices[faces_v[i][j]].getx(), vertices[faces_v[i][j]].gety(), vertices[faces_v[i][j]].getz());
	     glNormal3f(normals[faces_n[i][j]].getx(), normals[faces_n[i][j]].gety(), normals[faces_n[i][j]].getz());
	     glTexCoord2d(normals[faces_t[i][j]].getx(), normals[faces_t[i][j]].gety());
	  }
	  glEnd();
	}
	glFlush();
	glutSwapBuffers();
}
