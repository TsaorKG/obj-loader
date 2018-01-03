#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#define GL_GLEXT_PROTOTYPES
#endif

using namespace std;

class Texture {
private:
	unsigned long x;
	unsigned long y;
	unsigned short int bpp;      //bits per pixels   unsigned short int
	GLbyte* texData;             //the data of the image
	GLuint ID;                   //the id ogl gives it
	unsigned long size;          //length of the file
	int channels;                //the channels of the image 3 = RGA 4 = RGBA
	GLuint type;
	bool loaded;
public:
	Texture() {}
	Texture(char const* FileName, bool Fast); // LoadJPEG
	unsigned long getX() const { return x; }
	unsigned long getY() const { return y; }
	unsigned short int getBpp() const { return bpp; }
	GLbyte* getTexData() const { return texData; }
	GLuint getID() const { return ID; }
	unsigned long getSize() const { return size; }
	int getChannels() const { return channels; }
	GLuint getType() const { return type; }
	bool getLoaded() const { return loaded; }
};

#endif