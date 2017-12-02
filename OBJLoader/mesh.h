#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include <vector>
#include <string>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

using namespace std;

class Mesh {
private:
	// For loading OBJ files
	vector<Vector> vertices;
	vector<Vector> textures;
	vector<Vector> normals;
	vector< vector<int> > faces_v, faces_t, faces_n;
	int nbFaces;
	int nbVertices;
	int nbNormals;
	GLfloat angleX;
	GLfloat angleY;
	float zoom;
	// For loading MTL files
	string mtlFilename;
	vector<string> materialNames; // list of material names
	vector<string> textureFiles; // list of jpg files
	vector<Vector> Ka, Kd, Ks, Ke; // coefficients for each material used
	vector<float> Ns, d; // coefficients again
public:
	Mesh() { angleX=0.0f; angleY=0.0f; zoom = 1.0f; }
	vector<Vector> getVertices() const { return vertices; }
	vector<Vector> getNormals() const { return normals; }
	vector< vector<int> > getFaces_v() const { return faces_v; }
	vector< vector<int> > getFaces_t() const { return faces_t; }
	vector< vector<int> > getFaces_n() const { return faces_n; }
	int getNbFaces() const { return nbFaces; }
	int getNbVertices() const { return nbVertices; }
	int getNbNormals() const { return nbNormals; }
	bool readOBJ(const char* filename);
	bool readMTL(const char* filename);
	GLvoid affichage() const;
	float getZoom() const { return zoom; }
	void setZoom(float _zoom) { zoom = _zoom; }
	GLfloat getAngleX() const { return angleX; }
	GLfloat getAngleY() const { return angleY; }
	void setAngleX(GLfloat _angleX) { angleX = _angleX; }
	void setAngleY(GLfloat _angleY) { angleY = _angleY; }
	// Methods for MTL files
	string getMtlFilename() const { return mtlFilename; }
	vector<string> getMaterialNames() const { return materialNames; }
	vector<string> getTextureFiles() const { return textureFiles; }
	vector<Vector> getKa() const { return Ka; }
	vector<Vector> getKd() const { return Kd; }
	vector<Vector> getKs() const { return Ks; }
	vector<Vector> getKe() const { return Ke; }
	vector<float> getNs() const { return Ns; }
	vector<float> getD() const { return d; }
};

#endif
