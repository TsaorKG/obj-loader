#include "vector.h"
#include "texture.h"
#include "mesh.h"
#include "utilities.h"
#include <fstream>
#include <iostream>
#include "stdlib.h"
#include <string.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

using namespace std;

bool Mesh::readOBJ(const char* filename) {
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
				if (line[1] == 't') { // add vectors to textures list, converting strings to floats
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
					faces_t_tmp.push_back( atoi(((v2[1]=="")?"1":v2[1]).c_str()) -1);
					if (v2.size() > 2) { // in case there is no normal
						faces_n_tmp.push_back(atoi(v2[2].c_str())-1);
					}
				}
				if (faces_v_tmp.size() > 0) { faces_v.push_back(faces_v_tmp); }
				if (faces_t_tmp.size() > 0) { faces_t.push_back(faces_t_tmp); }
				if (faces_n_tmp.size() > 0) { faces_n.push_back(faces_n_tmp); }
			}
			if (line[0] == 'm') { // MTL filename
				mtlFilename = getMtlFilename(line);
				if (readMTL(mtlFilename.c_str()) == false) {
					cout << "Problem reading MTL file" << endl;
				}
			}
			if (line[0] == 'u') { // new material in use
				vector<string> v = split(line, ' ');
				faceTOmaterial a;
				a.materialIndex = index(materialNames, v[0]);
				a.faceIndex = faces_v.size(); // the next surface is the first surface with this material
				if (a.materialIndex > -1) { faceTOmaterial_v.push_back(a); }
			}
		}
		infile.close();
		nbFaces = faces_v.size();
		nbVertices = vertices.size();
		nbNormals = normals.size();
		return true;
	}
	return false;
}

bool Mesh::readMTL(const char* filename) {
	// Read MTL file, according to instructions in OBJ file.
	cout << "Reading MTL file " << filename << endl;
	ifstream infile (filename); // open the file in reading mode
	string line;
	if (infile.is_open()) {
		while (getline(infile, line)) {
			if (line[0] == 'n') { // newmtl
				vector<string> v = split(line, ' ');
				materialNames.push_back(v[0]); // add the new material to the material list
			}
			if (line[0] == 'N' && line[1] == 's') { // Ns
				vector<string> v = split(line, ' ');
				Ns.push_back(atof(v[0].c_str()));
			}
			if (line[0] == 'd') { // d
				vector<string> v = split(line, ' ');
				d.push_back(atof(v[0].c_str()));
			}
			if (line[0] == 'K' && line[1] == 'a') { // Ka
				vector<string> v = split(line, ' ');
				Ka.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str()),atof(v[2].c_str())));
			}
			if (line[0] == 'K' && line[1] == 'd') { // Kd
				vector<string> v = split(line, ' ');
				Kd.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str()),atof(v[2].c_str())));
			}
			if (line[0] == 'K' && line[1] == 's') { // Ks
				vector<string> v = split(line, ' ');
				Ks.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str()),atof(v[2].c_str())));
			}
			if (line[0] == 'K' && line[1] == 'e') { // Ke
				vector<string> v = split(line, ' ');
				Ke.push_back(Vector(atof(v[0].c_str()),atof(v[1].c_str()),atof(v[2].c_str())));
			}
			if (line[0] == 'm') { // map_Bump
				vector<string> v = split(line, ' ');
				vector<string> v2 = split(v[0], '/');
				textureFiles.push_back(v2[v2.size()-1]); // we take the jpg filename without the path
			}
		}
		infile.close();
		cout << "Reading done!" << endl;
		return true;
	}
	return false;
}

GLvoid Mesh::affichage() const {
	// Emptying frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection mode
	glMatrixMode(GL_MODELVIEW);

	// Rotation
	glLoadIdentity();
	glRotatef(-angleY,1.0f,0.0f,0.0f);
	glRotatef(-angleX,0.0f,1.0f,0.0f);
	// Scale
	glScalef(zoom,zoom,zoom);
	// Material Index in use
	int materialIndex = -1;

	// Enable textures
	glEnable(GL_TEXTURE_2D);

	// Draw a face at a time
	for(int i=0;i<nbFaces;i++) {
		glBegin(GL_POLYGON);
		// Optionnaly change material index in use
		for(int k=0; k<faceTOmaterial_v.size(); k++) {
			if (i == faceTOmaterial_v[k].faceIndex) { // the next surface needs a new material
				materialIndex = faceTOmaterial_v[k].materialIndex;
				light(materialIndex); // change the material in use
			}
		}
		for(int j=0;j<faces_v[i].size();j++) {
			if (vertices.size() > 0) {
				glVertex3f(vertices[faces_v[i][j]].getx(), vertices[faces_v[i][j]].gety(), vertices[faces_v[i][j]].getz());
				}
				if (normals.size() > 0) {
					glNormal3f(normals[faces_n[i][j]].getx(), normals[faces_n[i][j]].gety(), normals[faces_n[i][j]].getz());
				}
				if (textures.size() > 0) {
					glTexCoord2d(textures[faces_t[i][j]].getx(), textures[faces_t[i][j]].gety());
			}
		}
		glEnd();
	}
	glFlush();
	glutSwapBuffers();
}

void Mesh::light(int materialIndex) const {
	// set light
	GLfloat tmp[3];
	if (Ks.size() > 0) {
		VectorTOglfloat(Ks[materialIndex], tmp); // Converting a Vector to a GLfloat table
    	glLightfv(GL_LIGHT0, GL_SPECULAR, tmp); // Loading new light
	}
	if (Ka.size() > 0) { VectorTOglfloat(Ka[materialIndex], tmp); glLightfv(GL_LIGHT0, GL_AMBIENT, tmp); }
	if (Kd.size() > 0) { VectorTOglfloat(Kd[materialIndex], tmp); glLightfv(GL_LIGHT0, GL_DIFFUSE, tmp); }
	if (Ke.size() > 0) { VectorTOglfloat(Ke[materialIndex], tmp); glLightfv(GL_LIGHT0, GL_EMISSION, tmp); }
	if (Ns.size() > 0) {
		GLfloat tmp2[1];
		tmp2[0] = (GLfloat)Ns[materialIndex];
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, tmp2);
	}
	if (d.size() > 0) {  }
}
